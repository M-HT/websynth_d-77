/**
 *
 *  Copyright (C) 2025-2026 Roman Pauer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do
 *  so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#if (defined(__WIN32__) || defined(__WINDOWS__)) && !defined(_WIN32)
#define _WIN32
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#elif defined(__APPLE__)
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <mach/mach_init.h>
#include <mach/mach_vm.h>
#else
#define _GNU_SOURCE
#include <dlfcn.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#if !defined(MAP_FIXED_NOREPLACE) && defined(MAP_EXCL)
#define MAP_FIXED_NOREPLACE (MAP_FIXED | MAP_EXCL)
#endif
#endif

#include "functions-32bit.h"


extern void (*ptr_initialize_pointers)(uint64_t pointer_offset);

uint64_t pointer_offset;
unsigned int pointer_reserved_length;


int initialize_pointer_offset(void)
{
#ifdef _WIN32
    HMODULE hModule;
    uint64_t maddr, min_length, free_offset, free_length;
    void *mem;
    SYSTEM_INFO sinfo;
    MEMORY_BASIC_INFORMATION minfo;

    pointer_offset = 0;

    if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&ptr_initialize_pointers, &hModule))
    {
        return 1;
    }

    if (hModule == NULL)
    {
        return 2;
    }

    GetSystemInfo(&sinfo);

    min_length = (1024*1024 + 65536 + (sinfo.dwAllocationGranularity - 1)) & ~(sinfo.dwAllocationGranularity - 1);

    if ((uintptr_t)hModule <= 2*min_length)
    {
        pointer_reserved_length = 0;
        if (ptr_initialize_pointers != NULL)
        {
            ptr_initialize_pointers(pointer_offset);
        }
        return 0;
    }

    min_length = (1024*1024 + 65536 + (sinfo.dwPageSize - 1)) & ~(sinfo.dwPageSize - 1);

    maddr = free_offset = 0;
    for (;;)
    {
        if (0 == VirtualQuery((void *)maddr, &minfo, sizeof(minfo))) return 3;

        if (minfo.State == MEM_FREE)
        {
            if ((uintptr_t)minfo.BaseAddress <= (((minfo.RegionSize + (uintptr_t)minfo.BaseAddress) - min_length) & ~(uint64_t)(sinfo.dwAllocationGranularity - 1)))
            {
                free_offset = ((minfo.RegionSize + (uintptr_t)minfo.BaseAddress) - min_length) & ~(uint64_t)(sinfo.dwAllocationGranularity - 1);
                free_length = (minfo.RegionSize + (uintptr_t)minfo.BaseAddress) - free_offset;
            }
        }

        maddr = ((minfo.RegionSize + (uintptr_t)minfo.BaseAddress) + (sinfo.dwAllocationGranularity - 1)) & ~(uint64_t)(sinfo.dwAllocationGranularity - 1);

        if ((uintptr_t)hModule < maddr)
        {
            if (free_offset == 0) break;

            pointer_offset = free_offset;
            pointer_reserved_length = 0;

            // try reserving memory
            mem = VirtualAlloc((void *)free_offset, free_length, MEM_RESERVE, PAGE_NOACCESS);
            if (mem == (void *)free_offset)
            {
                pointer_reserved_length = (unsigned int)free_length;
            }
            else
            {
                if (mem != NULL) VirtualFree(mem, 0, MEM_RELEASE);
            }

            if (ptr_initialize_pointers != NULL)
            {
                ptr_initialize_pointers(pointer_offset);
            }
            return 0;
        }
    }

    return 4;
#elif defined(__APPLE__)
    Dl_info info;
    void *mem;
    long page_size;
    mach_port_t task;
    mach_vm_address_t region_address, maddr, free_offset;
    mach_vm_size_t region_size, min_length;
    vm_region_basic_info_data_64_t rinfo;
    mach_msg_type_number_t count;
    mach_port_t object_name;

    pointer_offset = 0;

    if (!dladdr(&ptr_initialize_pointers, &info))
    {
        return 1;
    }

    if (info.dli_fbase == NULL)
    {
        return 2;
    }

    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    min_length = (1024*1024 + 65536 + (page_size - 1)) & ~(page_size - 1);

    if ((uintptr_t)info.dli_fbase <= 2*min_length)
    {
        pointer_reserved_length = 0;
        if (ptr_initialize_pointers != NULL)
        {
            ptr_initialize_pointers(pointer_offset);
        }
        return 0;
    }

    task = current_task();

    maddr = free_offset = 0;
    for (;;)
    {
        region_address = maddr;
        count = VM_REGION_BASIC_INFO_COUNT_64;
        if (KERN_SUCCESS != mach_vm_region(task, &region_address, &region_size, VM_REGION_BASIC_INFO_64, (vm_region_info_t) &rinfo, &count, &object_name)) break;

        if (region_address - maddr >= min_length)
        {
            free_offset = region_address - min_length;
        }

        maddr = region_address + region_size;

        if ((uintptr_t)info.dli_fbase < maddr)
        {
            if (free_offset == 0) break;

            pointer_offset = free_offset;
            pointer_reserved_length = 0;

            // try reserving memory
            mem = mmap((void *)free_offset, min_length, PROT_NONE, MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
            if (mem == (void *)free_offset)
            {
                pointer_reserved_length = (unsigned int)min_length;
            }
            else
            {
                if (mem != MAP_FAILED) munmap(mem, min_length);
            }

            if (ptr_initialize_pointers != NULL)
            {
                ptr_initialize_pointers(pointer_offset);
            }
            return 0;
        }
    }

    return 4;
#else
    Dl_info info;
    void *mem;
    FILE *f;
    long page_size;
    int num_matches, flags;
    uintmax_t num0, num1, num2, min_length, free_offset;

    pointer_offset = 0;

    if (!dladdr(&ptr_initialize_pointers, &info))
    {
        return 1;
    }

    if (info.dli_fbase == NULL)
    {
        return 2;
    }

    f = fopen("/proc/self/maps", "rb");
    if (f == NULL)
    {
        char mapname[32];
        sprintf(mapname, "/proc/%"PRIuMAX"/map", (uintmax_t)getpid());
        f = fopen(mapname, "rb");
        if (f == NULL) return 3;
    }

    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    min_length = (1024*1024 + 65536 + (page_size - 1)) & ~(page_size - 1);

    if ((uintptr_t)info.dli_fbase <= 2*min_length)
    {
        pointer_reserved_length = 0;
        if (ptr_initialize_pointers != NULL)
        {
            ptr_initialize_pointers(pointer_offset);
        }
        return 0;
    }

    num0 = free_offset = 0;
    for (;;)
    {
        num_matches = fscanf(f, "%"SCNxMAX"%*[ -]%"SCNxMAX" %*[^\n^\r]%*[\n\r]", &num1, &num2);
        if ((num_matches == EOF) || (num_matches < 2)) break;

        // [num1 .. num2) block is used
        // [num0 .. num1) block is not used

        if (num1 - num0 >= min_length)
        {
            free_offset = num1 - min_length;
        }

        if (num2 > num0)
        {
            num0 = num2;
        }

        if ((uintptr_t)info.dli_fbase < num2)
        {
            if (free_offset == 0) break;

            pointer_offset = free_offset;
            pointer_reserved_length = 0;

            // try reserving memory
#if !defined(MAP_NORESERVE) && defined(MAP_GUARD)
            flags = MAP_GUARD;
#else
            flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
#endif

            mem = mmap((void *)free_offset, min_length, PROT_NONE, MAP_FIXED_NOREPLACE | flags, -1, 0);
            if (mem == (void *)free_offset)
            {
                pointer_reserved_length = (unsigned int)min_length;
            }
            else
            {
                if (mem != MAP_FAILED) munmap(mem, min_length);
            }

            fclose(f);
            if (ptr_initialize_pointers != NULL)
            {
                ptr_initialize_pointers(pointer_offset);
            }
            return 0;
        }
    }

    fclose(f);
    return 4;
#endif
}

void *map_memory_32bit(unsigned int size, int only_address_space)
{
#ifdef _WIN32
    uint64_t maddr, reg_base, reg_size;
    void *mem;
    SYSTEM_INFO sinfo;
    MEMORY_BASIC_INFORMATION minfo;

    if (size == 0) return NULL;

    GetSystemInfo(&sinfo);

    // round up requested size to the next page boundary
    size = (size + (sinfo.dwPageSize - 1)) & ~(sinfo.dwPageSize - 1);

    // set starting memory address
    maddr = pointer_offset + 1024*1024 + 65536;

    // round up starting memory address to the nearest multiple of the allocation granularity
    maddr = (maddr + (sinfo.dwAllocationGranularity - 1)) & ~(uintptr_t)(sinfo.dwAllocationGranularity - 1);

    // look for unused memory up to 2GB from pointer_offset
    while (maddr < pointer_offset + UINT64_C(0x80000000) && maddr + size <= pointer_offset + UINT64_C(0x80000000))
    {
        if (0 == VirtualQuery((void *)maddr, &minfo, sizeof(minfo))) return NULL;

        if (minfo.State == MEM_FREE)
        {
            reg_base = (((uintptr_t)minfo.BaseAddress) + (sinfo.dwAllocationGranularity - 1)) & ~(uintptr_t)(sinfo.dwAllocationGranularity - 1);
            if (minfo.RegionSize >= reg_base - (uintptr_t)minfo.BaseAddress)
            {
                reg_size = minfo.RegionSize - (reg_base - (uintptr_t)minfo.BaseAddress);

                if (reg_size >= size)
                {
                    mem = VirtualAlloc((void *)reg_base, size, MEM_RESERVE | (only_address_space ? 0 : MEM_COMMIT), only_address_space ? PAGE_NOACCESS : PAGE_READWRITE);
                    if (mem != NULL) return mem;
                }
            }
        }

        maddr = ((minfo.RegionSize + (uintptr_t)minfo.BaseAddress) + (sinfo.dwAllocationGranularity - 1)) & ~(uintptr_t)(sinfo.dwAllocationGranularity - 1);
    }

    return NULL;
#elif defined(__APPLE__)
    void *mem, *start;
    long page_size;
    int prot, flags;
    mach_port_t task;
    mach_vm_address_t region_address, free_region_start, free_region_end;
    mach_vm_size_t region_size;
    vm_region_basic_info_data_64_t info;
    mach_msg_type_number_t count;
    mach_port_t object_name;

    if (size == 0) return NULL;

    prot = only_address_space ? PROT_NONE : (PROT_READ | PROT_WRITE);
    flags = MAP_PRIVATE | MAP_ANONYMOUS | (only_address_space ? MAP_NORESERVE : 0);

    // look for unused memory up to 2GB from pointer_offset and try mapping memory there
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    task = current_task();

    region_address = pointer_offset;
    count = VM_REGION_BASIC_INFO_COUNT_64;
    if (KERN_SUCCESS != mach_vm_region(task, &region_address, &region_size, VM_REGION_BASIC_INFO_64, (vm_region_info_t) &info, &count, &object_name)) return NULL;

    // first free region (starting at address zero) belongs to segment __PAGEZERO, so don't try using memory here

    if (region_address >= pointer_offset + UINT64_C(0x80000000)) return NULL;

    free_region_start = region_address + region_size;
    while (free_region_start < pointer_offset + UINT64_C(0x80000000))
    {
        region_address = free_region_start;
        count = VM_REGION_BASIC_INFO_COUNT_64;
        if (KERN_SUCCESS != mach_vm_region(task, &region_address, &region_size, VM_REGION_BASIC_INFO_64, (vm_region_info_t) &info, &count, &object_name))
        {
            region_address = free_region_end = pointer_offset + UINT64_C(0x80000000);
            region_size = 0;
        }
        else
        {
            free_region_end = region_address;
            if (free_region_end >= pointer_offset + UINT64_C(0x80000000))
            {
                free_region_end = pointer_offset + UINT64_C(0x80000000);
                region_size = 0;
            }
        }

        if (free_region_end - free_region_start >= size)
        {
            // try using memory at the start of the free region
            start = (void *)free_region_start;
            mem = mmap(start, size, prot, MAP_FIXED | flags, -1, 0);
            if (mem == start) return mem;
            if (mem != MAP_FAILED)
            {
                munmap(start, size);
                goto error1;
            }

            // try using memory at the end of the free region
            start = (void *)((free_region_end - size) & ~(uintptr_t)(page_size - 1));
            if (start != (void *)free_region_start)
            {
                mem = mmap(start, size, prot, MAP_FIXED | flags, -1, 0);
                if (mem == start) return mem;
                if (mem != MAP_FAILED)
                {
                    munmap(start, size);
                    goto error1;
                }
            }
        }

        free_region_start = region_address + region_size;
    }

    return NULL;

error1:
    fprintf(stderr, "Error: memory mapped at different address\n");
    return NULL;
#else
    void *mem, *start;
    long page_size;
    FILE *f;
    int num_matches, prot, flags;
    uintmax_t num0, num1, num2;

    if (size == 0) return NULL;

    prot = only_address_space ? PROT_NONE : (PROT_READ | PROT_WRITE);

#if !defined(MAP_NORESERVE) && defined(MAP_GUARD)
    flags = only_address_space ? MAP_GUARD : (MAP_PRIVATE | MAP_ANONYMOUS);
#else
    flags = MAP_PRIVATE | MAP_ANONYMOUS | (only_address_space ? MAP_NORESERVE : 0);
#endif

    // look for unused memory up to 2GB from pointer_offset in memory maps and try mapping memory there
    f = fopen("/proc/self/maps", "rb");
    if (f == NULL)
    {
        char mapname[32];
        sprintf(mapname, "/proc/%"PRIuMAX"/map", (uintmax_t)getpid());
        f = fopen(mapname, "rb");
        if (f == NULL) return NULL;
    }

    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    mem = NULL;
    num0 = (pointer_offset + 1024*1024 + 65536 + (page_size - 1)) & ~(uintptr_t)(page_size - 1);
    while (num0 < pointer_offset + UINT64_C(0x80000000))
    {
        num_matches = fscanf(f, "%"SCNxMAX"%*[ -]%"SCNxMAX" %*[^\n^\r]%*[\n\r]", &num1, &num2);
        if ((num_matches == EOF) || (num_matches < 2)) break;

        // num1-num2 block is used
        // num0-num1 block is not used

        if (num1 > pointer_offset + UINT64_C(0x80000000))
        {
            num1 = pointer_offset + UINT64_C(0x80000000);
        }

        // num0-num1 block is below 2GB

        if ((num0 < num1) && (num1 - num0 >= size))
        {
            // try using memory at the start of the block
            start = (void *)num0;
            mem = mmap(start, size, prot, MAP_FIXED_NOREPLACE | flags, -1, 0);
            if (mem == start) break;
            if (mem != MAP_FAILED)
            {
                munmap(start, size);
                goto error2;
            }

            // try using memory at the end of the block
            start = (void *)((num1 - size) & ~(uintptr_t)(page_size - 1));
            if (start != (void *)num0)
            {
                mem = mmap(start, size, prot, MAP_FIXED_NOREPLACE | flags, -1, 0);
                if (mem == start) break;
                if (mem != MAP_FAILED)
                {
                    munmap(start, size);
                    goto error2;
                }
            }

            mem = NULL;
        }

        if (num2 > num0)
        {
            num0 = num2;
        }
    }

    fclose(f);

    if (mem != NULL) return mem;

    if ((num0 < pointer_offset + UINT64_C(0x80000000)) && (num0 + size <= pointer_offset + UINT64_C(0x80000000)))
    {
        // try using memory after the end of the last block
        start = (void *)num0;
        mem = mmap(start, size, prot, MAP_FIXED_NOREPLACE | flags, -1, 0);
        if (mem == start) return mem;
        if (mem != MAP_FAILED)
        {
            munmap(start, size);
            goto error1;
        }

        // try using memory at the end of 2GB
        start = (void *)((pointer_offset + UINT64_C(0x80000000) - size) & ~(uintptr_t)(page_size - 1));
        if (start != (void *)num0)
        {
            mem = mmap(start, size, prot, MAP_FIXED_NOREPLACE | flags, -1, 0);
            if (mem == start) return mem;
            if (mem != MAP_FAILED)
            {
                munmap(start, size);
                goto error1;
            }
        }
    }

    return NULL;

error2:
    fclose(f);

error1:
    fprintf(stderr, "Error: memory mapped at different address\n");
    return NULL;
#endif
}

void unmap_memory_32bit(void *mem, unsigned int size)
{
    if (mem != NULL && size != 0)
    {
#ifdef _WIN32
        VirtualFree(mem, 0, MEM_RELEASE);
#else
        munmap(mem, size);
#endif
    }
}

