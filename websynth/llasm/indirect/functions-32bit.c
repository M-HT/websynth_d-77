/**
 *
 *  Copyright (C) 2025 Roman Pauer
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
#include <stdio.h>
#if !defined(IMAGE_SIZEOF_BASE_RELOCATION)
#define IMAGE_SIZEOF_BASE_RELOCATION 8
#endif
#if !defined(IMAGE_SIZEOF_NT_OPTIONAL64_HEADER)
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER 240
#endif
#else
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#if !defined(MAP_FIXED_NOREPLACE) && defined(MAP_EXCL)
#define MAP_FIXED_NOREPLACE (MAP_FIXED | MAP_EXCL)
#endif
#if !defined(R_X86_64_JUMP_SLOT) && defined(R_X86_64_JMP_SLOT)
#define R_X86_64_JUMP_SLOT R_X86_64_JMP_SLOT
#endif
#if !defined(DT_NUM)
#define DT_NUM 38
#endif
#endif

#include "functions-32bit.h"
#include "symbol-table.h"

// ELF Format Cheatsheet:
// https://gist.github.com/x0nu11byt3/bcb35c3de461e5fb66173071a2379779


#ifdef _WIN32
static void *reserve_address_space(uintptr_t maddr, unsigned int size)
{
    void *mem;
    MEMORY_BASIC_INFORMATION minfo;

    if (0 == VirtualQuery((void *)maddr, &minfo, sizeof(minfo))) return NULL;

    if (minfo.State == MEM_FREE)
    {
        if (minfo.RegionSize + (uintptr_t)minfo.BaseAddress >= maddr + size)
        {
            mem = VirtualAlloc((void *)maddr, size, MEM_RESERVE, PAGE_NOACCESS);
            if (mem == (void *)maddr) return mem;
            if (mem != NULL)VirtualFree(mem, 0, MEM_RELEASE);
        }
    }

    return NULL;
}
#endif

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
    maddr = 1024*1024 + 65536;

    // round up starting memory address to the nearest multiple of the allocation granularity
    maddr = (maddr + (sinfo.dwAllocationGranularity - 1)) & ~(sinfo.dwAllocationGranularity - 1);

    // look for unused memory below 2GB
    while (maddr < UINT64_C(0x80000000) && maddr + size <= UINT64_C(0x80000000))
    {
        if (0 == VirtualQuery((void *)maddr, &minfo, sizeof(minfo))) return NULL;

        if (minfo.State == MEM_FREE)
        {
            reg_base = (((uintptr_t)minfo.BaseAddress) + (sinfo.dwAllocationGranularity - 1)) & ~(sinfo.dwAllocationGranularity - 1);
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

        maddr = ((minfo.RegionSize + (uintptr_t)minfo.BaseAddress) + (sinfo.dwAllocationGranularity - 1)) & ~(sinfo.dwAllocationGranularity - 1);
    }

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

    // if platform supports MAP_32BIT, then try mapping memory with it
#if defined(MAP_32BIT) && (MAP_32BIT != 0)
    mem = mmap(0, size, prot, MAP_32BIT | flags, -1, 0);
    if (mem != MAP_FAILED)
    {
        if (((uintptr_t)mem >= UINT64_C(0x80000000)) || (size + (uintptr_t)mem > UINT64_C(0x80000000)))
        {
            // mapped memory is above 2GB
            munmap(mem, size);
        }
        else
        {
            return mem;
        }
    }
#endif

    // look for unused memory below 2GB in memory maps and try mapping memory there
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
    num0 = (1024*1024 + 65536 + (page_size - 1)) & ~(page_size - 1);
    while (num0 < UINT64_C(0x80000000))
    {
        num_matches = fscanf(f, "%"SCNxMAX"%*[ -]%"SCNxMAX" %*[^\n^\r]%*[\n\r]", &num1, &num2);
        if ((num_matches == EOF) || (num_matches < 2)) break;

        // num1-num2 block is used
        // num0-num1 block is not used

        if (num1 > UINT64_C(0x80000000))
        {
            num1 = UINT64_C(0x80000000);
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
            start = (void *)((num1 - size) & ~(page_size - 1));
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

    if ((num0 < UINT64_C(0x80000000)) && (num0 + size <= UINT64_C(0x80000000)))
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
        start = (void *)((UINT64_C(0x80000000) - size) & ~(page_size - 1));
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


#ifdef _WIN32

static uint8_t *load_library_from_memory_windows(uint8_t *mem)
{
    PIMAGE_DOS_HEADER dos_header;
    PIMAGE_NT_HEADERS64 nt_headers;
    PIMAGE_SECTION_HEADER sec_headers;
    int index;
    uint32_t min_addr, first_addr, max_addr;
    void *mapped_addr;
    uint8_t *base_addr, *section;
    uint32_t filesz;
    DWORD oldprot;
    SYSTEM_INFO sinfo;

    dos_header = (PIMAGE_DOS_HEADER) mem;

    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) return NULL;

    nt_headers = (PIMAGE_NT_HEADERS64) (mem + dos_header->e_lfanew);

    if (nt_headers->Signature != IMAGE_NT_SIGNATURE ||
        (nt_headers->FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64 && nt_headers->FileHeader.Machine != IMAGE_FILE_MACHINE_ARM64) ||
        nt_headers->FileHeader.NumberOfSections == 0 ||
        nt_headers->FileHeader.SizeOfOptionalHeader < IMAGE_SIZEOF_NT_OPTIONAL64_HEADER ||
        (nt_headers->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0 ||
        (nt_headers->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0 ||
        (nt_headers->FileHeader.Characteristics & IMAGE_FILE_RELOCS_STRIPPED) != 0 ||
        nt_headers->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC ||
        nt_headers->OptionalHeader.Subsystem != IMAGE_SUBSYSTEM_WINDOWS_CUI ||
        nt_headers->OptionalHeader.NumberOfRvaAndSizes < IMAGE_NUMBEROF_DIRECTORY_ENTRIES
       ) return NULL;

    GetSystemInfo(&sinfo);

    sec_headers = (PIMAGE_SECTION_HEADER)((uintptr_t)nt_headers + FIELD_OFFSET(IMAGE_NT_HEADERS64, OptionalHeader) + nt_headers->FileHeader.SizeOfOptionalHeader);

    // get minimum and maximum address for loading
    max_addr = 0;
    min_addr = (int32_t)-1;
    for (index = 0; index < nt_headers->FileHeader.NumberOfSections; index++)
    {
        if (sec_headers[index].VirtualAddress < min_addr)
        {
            min_addr = sec_headers[index].VirtualAddress;
        }
        if (sec_headers[index].VirtualAddress + sec_headers[index].Misc.VirtualSize > max_addr)
        {
            max_addr = sec_headers[index].VirtualAddress + sec_headers[index].Misc.VirtualSize;
        }
    }

    if (min_addr < sizeof(IMAGE_NT_HEADERS64) + nt_headers->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER))
    {
        fprintf(stderr, "Error: insufficient space for headers\n");
        return NULL;
    }

    // make space for headers
    first_addr = min_addr;
    min_addr -= sizeof(IMAGE_NT_HEADERS64) + nt_headers->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);

    // round down minimum address to allocation granularity
    min_addr = min_addr & ~(sinfo.dwAllocationGranularity - 1);
    // round up maximum address to page boundary
    max_addr = (max_addr + (sinfo.dwPageSize - 1)) & ~(sinfo.dwPageSize - 1);

    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size == 0)
    {
        mapped_addr = reserve_address_space(nt_headers->OptionalHeader.ImageBase + min_addr, max_addr - min_addr);
    }
    else
    {
        mapped_addr = map_memory_32bit(max_addr - min_addr, 1);
    }
    if (mapped_addr == NULL) return NULL;

    base_addr = (uint8_t *)((uintptr_t)mapped_addr - min_addr);

    // map sections into memory
    for (index = 0; index < nt_headers->FileHeader.NumberOfSections; index++)
    {
        section = (uint8_t *)VirtualAlloc(base_addr + sec_headers[index].VirtualAddress, sec_headers[index].Misc.VirtualSize, MEM_COMMIT, PAGE_READWRITE);
        if (section == NULL) goto error1;

        filesz = sec_headers[index].SizeOfRawData;
        if (sec_headers[index].Misc.VirtualSize < sec_headers[index].SizeOfRawData) filesz = sec_headers[index].Misc.VirtualSize;

        if (filesz != 0)
        {
            CopyMemory(base_addr + sec_headers[index].VirtualAddress, mem + sec_headers[index].PointerToRawData, filesz);
        }
    }

    // copy headers
    if (first_addr - min_addr >= sinfo.dwPageSize)
    {
        section = (uint8_t *)VirtualAlloc(mapped_addr, sizeof(IMAGE_NT_HEADERS64) + nt_headers->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), MEM_COMMIT, PAGE_READWRITE);
        if (section == NULL) goto error1;
    } else section = (uint8_t *)mapped_addr;

    CopyMemory(section, nt_headers, sizeof(IMAGE_NT_HEADERS64));
    CopyMemory(section + sizeof(IMAGE_NT_HEADERS64), sec_headers, nt_headers->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER));

    ((PIMAGE_NT_HEADERS64)section)->FileHeader.SizeOfOptionalHeader = IMAGE_SIZEOF_NT_OPTIONAL64_HEADER;
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.DataDirectory[15].VirtualAddress = min_addr; // unused DataDirectory
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.DataDirectory[15].Size = max_addr - min_addr;

    if (first_addr - min_addr >= sinfo.dwPageSize)
    {
        VirtualProtect(mapped_addr, sizeof(IMAGE_NT_HEADERS64) + nt_headers->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), PAGE_READONLY, &oldprot);
    }

    return (uint8_t *)mapped_addr;

error1:
    VirtualFree(mapped_addr, 0, MEM_RELEASE);
    return NULL;
}

static uint8_t *load_library_from_file_windows(HANDLE file)
{
    PIMAGE_SECTION_HEADER sec_headers;
    DWORD bytes_read;
    HANDLE heap;
    int index;
    uint32_t min_addr, first_addr, max_addr;
    void *mapped_addr;
    uint8_t *base_addr, *section;
    uint32_t filesz;
    DWORD oldprot;
    IMAGE_DOS_HEADER dos_header;
    IMAGE_NT_HEADERS64 nt_headers;
    SYSTEM_INFO sinfo;

    ReadFile(file, &dos_header, sizeof(IMAGE_DOS_HEADER), &bytes_read, NULL);
    if (bytes_read != sizeof(IMAGE_DOS_HEADER)) return NULL;

    if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) return NULL;

    if (SetFilePointer(file, dos_header.e_lfanew, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) return NULL;

    ReadFile(file, &nt_headers, sizeof(IMAGE_NT_HEADERS64), &bytes_read, NULL);
    if (bytes_read != sizeof(IMAGE_NT_HEADERS64)) return NULL;

    if (nt_headers.Signature != IMAGE_NT_SIGNATURE ||
        (nt_headers.FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64 && nt_headers.FileHeader.Machine != IMAGE_FILE_MACHINE_ARM64) ||
        nt_headers.FileHeader.NumberOfSections == 0 ||
        nt_headers.FileHeader.SizeOfOptionalHeader < IMAGE_SIZEOF_NT_OPTIONAL64_HEADER ||
        (nt_headers.FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0 ||
        (nt_headers.FileHeader.Characteristics & IMAGE_FILE_DLL) == 0 ||
        (nt_headers.FileHeader.Characteristics & IMAGE_FILE_RELOCS_STRIPPED) != 0 ||
        nt_headers.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC ||
        nt_headers.OptionalHeader.Subsystem != IMAGE_SUBSYSTEM_WINDOWS_CUI ||
        nt_headers.OptionalHeader.NumberOfRvaAndSizes < IMAGE_NUMBEROF_DIRECTORY_ENTRIES
       ) return NULL;

    heap = GetProcessHeap();

    if (SetFilePointer(file, dos_header.e_lfanew + FIELD_OFFSET(IMAGE_NT_HEADERS64, OptionalHeader) + nt_headers.FileHeader.SizeOfOptionalHeader, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) return NULL;

    sec_headers = (PIMAGE_SECTION_HEADER)HeapAlloc(heap, 0, nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER));
    if (sec_headers == NULL) return NULL;

    ReadFile(file, sec_headers, nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), &bytes_read, NULL);
    if (bytes_read != nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER)) goto error1;

    GetSystemInfo(&sinfo);

    // get minimum and maximum address for loading
    max_addr = 0;
    min_addr = (int32_t)-1;
    for (index = 0; index < nt_headers.FileHeader.NumberOfSections; index++)
    {
        if (sec_headers[index].VirtualAddress < min_addr)
        {
            min_addr = sec_headers[index].VirtualAddress;
        }
        if (sec_headers[index].VirtualAddress + sec_headers[index].Misc.VirtualSize > max_addr)
        {
            max_addr = sec_headers[index].VirtualAddress + sec_headers[index].Misc.VirtualSize;
        }
    }

    if (min_addr < sizeof(IMAGE_NT_HEADERS64) + nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER))
    {
        fprintf(stderr, "Error: insufficient space for headers\n");
        goto error1;
    }

    // make space for headers
    first_addr = min_addr;
    min_addr -= sizeof(IMAGE_NT_HEADERS64) + nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);

    // round down minimum address to allocation granularity
    min_addr = min_addr & ~(sinfo.dwAllocationGranularity - 1);
    // round up maximum address to page boundary
    max_addr = (max_addr + (sinfo.dwPageSize - 1)) & ~(sinfo.dwPageSize - 1);

    if (nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size == 0)
    {
        mapped_addr = reserve_address_space(nt_headers.OptionalHeader.ImageBase + min_addr, max_addr - min_addr);
    }
    else
    {
        mapped_addr = map_memory_32bit(max_addr - min_addr, 1);
    }
    if (mapped_addr == NULL) goto error1;

    base_addr = (uint8_t *)((uintptr_t)mapped_addr - min_addr);

    // map sections into memory
    for (index = 0; index < nt_headers.FileHeader.NumberOfSections; index++)
    {
        section = (uint8_t *)VirtualAlloc(base_addr + sec_headers[index].VirtualAddress, sec_headers[index].Misc.VirtualSize, MEM_COMMIT, PAGE_READWRITE);
        if (section == NULL) goto error2;

        filesz = sec_headers[index].SizeOfRawData;
        if (sec_headers[index].Misc.VirtualSize < sec_headers[index].SizeOfRawData) filesz = sec_headers[index].Misc.VirtualSize;

        if (filesz != 0)
        {
            if (SetFilePointer(file, sec_headers[index].PointerToRawData, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) goto error2;

            ReadFile(file, base_addr + sec_headers[index].VirtualAddress, filesz, &bytes_read, NULL);
            if (bytes_read != filesz) goto error2;
        }
    }

    // copy headers
    if (first_addr - min_addr >= sinfo.dwPageSize)
    {
        section = (uint8_t *)VirtualAlloc(mapped_addr, sizeof(IMAGE_NT_HEADERS64) + nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), MEM_COMMIT, PAGE_READWRITE);
        if (section == NULL) goto error2;
    } else section = (uint8_t *)mapped_addr;

    CopyMemory(section, &nt_headers, sizeof(IMAGE_NT_HEADERS64));
    CopyMemory(section + sizeof(IMAGE_NT_HEADERS64), sec_headers, nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER));

    ((PIMAGE_NT_HEADERS64)section)->FileHeader.SizeOfOptionalHeader = IMAGE_SIZEOF_NT_OPTIONAL64_HEADER;
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.DataDirectory[15].VirtualAddress = min_addr; // unused DataDirectory
    ((PIMAGE_NT_HEADERS64)section)->OptionalHeader.DataDirectory[15].Size = max_addr - min_addr;

    if (first_addr - min_addr >= sinfo.dwPageSize)
    {
        VirtualProtect(mapped_addr, sizeof(IMAGE_NT_HEADERS64) + nt_headers.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), PAGE_READONLY, &oldprot);
    }

    HeapFree(heap, 0, sec_headers);

    return (uint8_t *)mapped_addr;

error2:
    VirtualFree(mapped_addr, 0, MEM_RELEASE);

error1:
    HeapFree(heap, 0, sec_headers);
    return NULL;
}

#else

static long int read2(int fd, void *buf, unsigned long int count)
{
    long int res;
    unsigned long int count2;

    count2 = 0;
    while (1)
    {
        res = read(fd, buf, count);
        if (res < 0) return res; // error

        if (res == 0) return count2; // end of file

        count2 += res;
        count -= res;

        if (count == 0) return count2; // full buffer

        buf = (void *) (res + (uintptr_t)buf);
    }
}

static uint8_t *load_library_from_file_linux(int fd, uint64_t *libsize)
{
    Elf64_Ehdr elf_header;
    uint8_t *program_headers;
    Elf64_Phdr *program_header;
    uint8_t *base_addr, *start, *segment;
    int64_t page_size;
    uint64_t min_addr, max_addr, length, page_offset, filesz;
    int index, prot;

    if (lseek(fd, 0, SEEK_SET) < 0) goto error1;

    if (read2(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header)) goto error1;

    if ((elf_header.e_ident[EI_MAG0] != ELFMAG0) ||
        (elf_header.e_ident[EI_MAG1] != ELFMAG1) ||
        (elf_header.e_ident[EI_MAG2] != ELFMAG2) ||
        (elf_header.e_ident[EI_MAG3] != ELFMAG3) ||
        (elf_header.e_ident[EI_CLASS] != ELFCLASS64) ||
        (elf_header.e_ident[EI_VERSION] != EV_CURRENT) ||
        (elf_header.e_type != ET_DYN) ||
        (elf_header.e_phentsize == 0) ||
        (elf_header.e_phnum == 0)
       ) goto error1;

    if (lseek(fd, elf_header.e_phoff, SEEK_SET) < 0) goto error1;

    program_headers = (uint8_t *)malloc(elf_header.e_phentsize * elf_header.e_phnum);
    if (program_headers == NULL) goto error1;

    if (read2(fd, program_headers, elf_header.e_phentsize * elf_header.e_phnum) != elf_header.e_phentsize * elf_header.e_phnum) goto error2;

    // get page size
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    // get minimum and maximum address for loading
    max_addr = 0;
    min_addr = (int64_t)-1;
    for (index = 0; index < elf_header.e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(program_headers + index * elf_header.e_phentsize);

        if (program_header->p_type != PT_LOAD) continue;

        if (program_header->p_vaddr < min_addr)
        {
            min_addr = program_header->p_vaddr;
        }
        if (program_header->p_vaddr + program_header->p_memsz > max_addr)
        {
            max_addr = program_header->p_vaddr + program_header->p_memsz;
        }
    }

    // align minimum and maximum address to page size
    min_addr = min_addr & ~(page_size - 1);
    max_addr = (max_addr + (page_size - 1)) & ~(page_size - 1);

    if (min_addr != 0)
    {
        fprintf(stderr, "Error: headers not loaded\n");
        goto error2;
    }

    base_addr = (uint8_t *) map_memory_32bit(max_addr, 1);
    if (base_addr == NULL) goto error2;

    // load segments into memory
    for (index = 0; index < elf_header.e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(program_headers + index * elf_header.e_phentsize);

        if (program_header->p_type != PT_LOAD) continue;

        page_offset = program_header->p_vaddr & (page_size - 1);
        start = base_addr + program_header->p_vaddr - page_offset;
        length = (page_offset + program_header->p_memsz + (page_size - 1)) & ~(page_size - 1);

        prot = PROT_NONE;
        if (program_header->p_flags & PF_X) prot |= PROT_EXEC;
        if (program_header->p_flags & PF_W) prot |= PROT_WRITE;
        if (program_header->p_flags & PF_R) prot |= PROT_READ;

        segment = (uint8_t *)mmap(start, length, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
        if (segment == MAP_FAILED) goto error3;

        filesz = program_header->p_filesz;
        if (program_header->p_memsz < filesz) filesz = program_header->p_memsz;

        if (filesz != 0)
        {
            if (lseek(fd, program_header->p_offset, SEEK_SET) < 0) goto error3;

            if (read2(fd, segment + page_offset, filesz) != filesz) goto error3;

            if (program_header->p_flags & PF_X)
            {
                __builtin___clear_cache((char *)(segment + page_offset), (char *)(segment + page_offset + filesz));
            }
        }

        if (mprotect(segment, length, prot) < 0) goto error3;
    }

    free(program_headers);

    *libsize = max_addr;
    return base_addr;

error3:
    munmap(base_addr, max_addr);

error2:
    free(program_headers);

error1:
    return NULL;
}

static uint8_t *load_library_from_memory_linux(int fd, uint8_t *mem, uint64_t *libsize)
{
    Elf64_Ehdr *elf_header;
    Elf64_Phdr *program_header;
    uint8_t *base_addr, *start, *segment;
    int64_t page_size;
    uint64_t min_addr, max_addr, length, page_offset, filesz;
    int index, prot;

    elf_header = (Elf64_Ehdr *)mem;

    if ((elf_header->e_ident[EI_MAG0] != ELFMAG0) ||
        (elf_header->e_ident[EI_MAG1] != ELFMAG1) ||
        (elf_header->e_ident[EI_MAG2] != ELFMAG2) ||
        (elf_header->e_ident[EI_MAG3] != ELFMAG3) ||
        (elf_header->e_ident[EI_CLASS] != ELFCLASS64) ||
        (elf_header->e_ident[EI_VERSION] != EV_CURRENT) ||
        (elf_header->e_type != ET_DYN) ||
        (elf_header->e_phentsize == 0) ||
        (elf_header->e_phnum == 0)
       ) goto error1;

    // get page size
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    // get minimum and maximum address for loading
    max_addr = 0;
    min_addr = (int64_t)-1;
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(mem + elf_header->e_phoff + index * elf_header->e_phentsize);

        if (program_header->p_type != PT_LOAD) continue;

        if (program_header->p_vaddr < min_addr)
        {
            min_addr = program_header->p_vaddr;
        }
        if (program_header->p_vaddr + program_header->p_memsz > max_addr)
        {
            max_addr = program_header->p_vaddr + program_header->p_memsz;
        }
    }

    // align minimum and maximum address to page size
    min_addr = min_addr & ~(page_size - 1);
    max_addr = (max_addr + (page_size - 1)) & ~(page_size - 1);

    if (min_addr != 0)
    {
        fprintf(stderr, "Error: headers not loaded\n");
        goto error1;
    }

    base_addr = (uint8_t *) map_memory_32bit(max_addr, 1);
    if (base_addr == NULL) goto error1;

    // map segments into memory
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(mem + elf_header->e_phoff + index * elf_header->e_phentsize);

        if (program_header->p_type != PT_LOAD) continue;

        page_offset = program_header->p_vaddr & (page_size - 1);
        start = base_addr + program_header->p_vaddr - page_offset;
        length = (page_offset + program_header->p_memsz + (page_size - 1)) & ~(page_size - 1);

        prot = PROT_NONE;
        if (program_header->p_flags & PF_X) prot |= PROT_EXEC;
        if (program_header->p_flags & PF_W) prot |= PROT_WRITE;
        if (program_header->p_flags & PF_R) prot |= PROT_READ;

        if ((page_offset == 0) && (program_header->p_filesz == program_header->p_memsz) && !(program_header->p_offset & (page_size - 1)))
        {
            segment = (uint8_t *)mmap(start, program_header->p_filesz, prot, MAP_PRIVATE | MAP_FIXED, fd, program_header->p_offset);
            if (segment == MAP_FAILED) goto error2;
        }
        else
        {
            segment = (uint8_t *)mmap(start, length, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
            if (segment == MAP_FAILED) goto error2;

            filesz = program_header->p_filesz;
            if (program_header->p_memsz < filesz) filesz = program_header->p_memsz;

            if (filesz != 0)
            {
                memcpy(segment + page_offset, mem + program_header->p_offset, filesz);

                if (program_header->p_flags & PF_X)
                {
                    __builtin___clear_cache((char *)(segment + page_offset), (char *)(segment + page_offset + filesz));
                }
            }

            if (mprotect(segment, length, prot) < 0) goto error2;
        }
    }

    *libsize = max_addr;
    return base_addr;

error2:
    munmap(base_addr, max_addr);

error1:
    return NULL;
}

#endif

void *load_library_32bit(const char *libpath)
{
#ifdef _WIN32
    HANDLE file, fmap;
    LARGE_INTEGER fsize;
    uint8_t *mem, *library, *base_addr;
    PIMAGE_NT_HEADERS64 nt_headers;
    PIMAGE_SECTION_HEADER sec_headers;
    PIMAGE_BASE_RELOCATION base_reloc;
    PIMAGE_IMPORT_DESCRIPTOR import_desc;
    void *import_value;
    const char *dll_name, *import_name;
    uint64_t *import_lookup, *import_address;
    HANDLE process;
    unsigned int index, indsymb;
    uint32_t prot, reloc_offset1, reloc_offset2, reloc_type, page_offset;
    DWORD oldprot;

    if (sizeof(void *) != 8) return NULL;

    // open file
    file = CreateFile(libpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return NULL;

    if (!GetFileSizeEx(file, &fsize) || fsize.QuadPart < (LONGLONG)(sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64))) // error getting size or file is smaller than headers
    {
        CloseHandle(file);
        return NULL;
    }

    fmap = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
    if (fmap != INVALID_HANDLE_VALUE)
    {
        mem = (uint8_t *) MapViewOfFile(fmap, FILE_MAP_READ, 0, 0, 0);
        if (mem == NULL)
        {
            CloseHandle(fmap);
        }
    } else mem = NULL;

    if (mem != NULL)
    {
        library = load_library_from_memory_windows(mem);
        UnmapViewOfFile(mem);
        CloseHandle(fmap);
        CloseHandle(file);
    }
    else
    {
        library = load_library_from_file_windows(file);
        CloseHandle(file);
    }

    if (library == NULL) return NULL;

    nt_headers = (PIMAGE_NT_HEADERS64)library;
    sec_headers = (PIMAGE_SECTION_HEADER)((uintptr_t)nt_headers + FIELD_OFFSET(IMAGE_NT_HEADERS64, OptionalHeader) + nt_headers->FileHeader.SizeOfOptionalHeader);

    base_addr = library - nt_headers->OptionalHeader.DataDirectory[15].VirtualAddress;

    if (nt_headers->OptionalHeader.AddressOfEntryPoint != 0)
    {
        fprintf(stderr, "Error: unsuported entry point\n");
        goto error1;
    }

    // apply relocations
    reloc_offset1 = 0;
    while (reloc_offset1 < nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size)
    {
        base_reloc = (PIMAGE_BASE_RELOCATION)(base_addr + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress + reloc_offset1);
        if (base_reloc->SizeOfBlock == 0) break;

        reloc_offset2 = IMAGE_SIZEOF_BASE_RELOCATION;
        while (reloc_offset2 < base_reloc->SizeOfBlock)
        {
            reloc_type = *(uint16_t *)((uintptr_t)base_reloc + reloc_offset2) >> 12;
            page_offset = *(uint16_t *)((uintptr_t)base_reloc + reloc_offset2) & 0x0fff;
            if (reloc_type == IMAGE_REL_BASED_HIGHLOW)
            {
                *(uint32_t *)(base_addr + base_reloc->VirtualAddress + page_offset) += (int32_t)((intptr_t)base_addr - nt_headers->OptionalHeader.ImageBase);
            }
            else if (reloc_type == IMAGE_REL_BASED_DIR64)
            {
                *(uint64_t *)(base_addr + base_reloc->VirtualAddress + page_offset) += (intptr_t)base_addr - nt_headers->OptionalHeader.ImageBase;
            }
            else if (reloc_type != IMAGE_REL_BASED_ABSOLUTE)
            {
                fprintf(stderr, "Error: unsuported relocation type\n");
                goto error1;
            }

            reloc_offset2 += 2;
        }

        reloc_offset1 += base_reloc->SizeOfBlock;
    }

    // apply external symbols
    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size != 0 && nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size != 0)
    {
        import_desc = (PIMAGE_IMPORT_DESCRIPTOR)(base_addr + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

        while (import_desc->OriginalFirstThunk != 0)
        {
            if (import_desc->ForwarderChain != 0)
            {
                fprintf(stderr, "Error: unsuported DLL forwarding\n");
                goto error1;
            }

            dll_name = (const char *)(base_addr + import_desc->Name);
            if (dll_name[0] != 0 && strcmp(dll_name, "(null)") != 0 && strcmp(dll_name, ".(null)") != 0)
            {
                fprintf(stderr, "Error: unsuported DLL importing\n");
                goto error1;
            }

            import_lookup = (uint64_t *)(base_addr + import_desc->OriginalFirstThunk);
            import_address = (uint64_t *)(base_addr + import_desc->FirstThunk);

            for (; *import_lookup != 0; import_lookup++, import_address++)
            {
                if (*import_lookup & UINT64_C(0x8000000000000000))
                {
                    fprintf(stderr, "Error: unsuported import by ordinal\n");
                    goto error1;
                }

                import_name = (const char *)((PIMAGE_IMPORT_BY_NAME)(base_addr + (*import_lookup & 0x7fffffff)))->Name;

                import_value = NULL;
                for (indsymb = 0; indsymb < sizeof(symbol_table)/sizeof(symbol_table[0]); indsymb++)
                {
                    if (0 == strcmp(import_name, symbol_table[indsymb].name))
                    {
                        import_value = symbol_table[indsymb].value;
                        break;
                    }
                }

                if (import_value == NULL)
                {
                    fprintf(stderr, "Error: import not found: %s\n", import_name);
                    goto error1;
                }

                *import_address = (uintptr_t)import_value;
            }

            import_desc++;
        }
    }

    // discard unneeded pages / set protection on pages
    process = GetCurrentProcess();
    for (index = 0; index < nt_headers->FileHeader.NumberOfSections; index++)
    {
        if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_DISCARDABLE)
        {
            VirtualFree(base_addr + sec_headers[index].VirtualAddress, sec_headers[index].Misc.VirtualSize, MEM_DECOMMIT);
            continue;
        }

        if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_EXECUTE)
        {
            if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_WRITE) prot = PAGE_EXECUTE_READWRITE;
            else if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_READ) prot = PAGE_EXECUTE_READ;
            else prot = PAGE_EXECUTE;

            FlushInstructionCache(process, base_addr + sec_headers[index].VirtualAddress, sec_headers[index].Misc.VirtualSize);
        }
        else if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_WRITE) prot = PAGE_READWRITE;
        else if (sec_headers[index].Characteristics & IMAGE_SCN_MEM_READ) prot = PAGE_READONLY;
        else prot = PAGE_NOACCESS;

        if (prot != PAGE_READWRITE)
        {
            if (!VirtualProtect(base_addr + sec_headers[index].VirtualAddress, sec_headers[index].Misc.VirtualSize, prot, &oldprot)) goto error1;
        }
    }

    return library;

error1:
    VirtualFree(library, 0, MEM_RELEASE);
    return NULL;
#else
    int fd, index, indrel, indsymb;
    off_t len;
    uint8_t *mem, *library;
    uint64_t libsize, section_offset, relsize, reladdr;
    Elf64_Ehdr *elf_header;
    Elf64_Phdr *program_header;
    Elf64_Dyn *dynamic_entry;
    Elf64_Rela *relocation;
    Elf64_Sym *symbol;
    const char *symbname;
    void *symbvalue;
    uint64_t dynamic_entries[DT_NUM+1];

    if (sizeof(void *) != 8) return NULL;

    // open file
    fd = open(libpath, O_RDONLY);
    if (fd < 0) return NULL;

    len = lseek(fd, 0, SEEK_END);
    if (len < sizeof(Elf64_Ehdr)) // error seeking or file is smaller than 64-bit elf header
    {
        close(fd);
        return NULL;
    }

    // map whole file into memory
    mem = (uint8_t *) mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem != MAP_FAILED)
    {
        library = load_library_from_memory_linux(fd, mem, &libsize);
        munmap(mem, len);
        close(fd);
    }
    else
    {
        library = load_library_from_file_linux(fd, &libsize);
        close(fd);
    }

    if (library == NULL) return NULL;

    elf_header = (Elf64_Ehdr *)library;

    if ((elf_header->e_machine != EM_X86_64) && (elf_header->e_machine != EM_AARCH64))
    {
        fprintf(stderr, "Error: unsuported machine type\n");
        goto error1;
    }

    // read dynamic entries
    memset(dynamic_entries, 0, sizeof(dynamic_entries));
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(library + elf_header->e_phoff + index * elf_header->e_phentsize);

        if (program_header->p_type != PT_DYNAMIC) continue;

        for (section_offset = 0; section_offset < program_header->p_memsz; section_offset += sizeof(Elf64_Dyn))
        {
            dynamic_entry = (Elf64_Dyn *)(library + program_header->p_vaddr + section_offset);

            if (dynamic_entry->d_tag < sizeof(dynamic_entries) / sizeof(dynamic_entries[0]))
            {
                dynamic_entries[dynamic_entry->d_tag] = dynamic_entry->d_un.d_val;
            }
        }
    }

    // unsupported: loading libraries

    // apply relocations and external symbols
    if (dynamic_entries[DT_RELSZ] != 0)
    {
        fprintf(stderr, "Error: unsuported relocation section type\n");
        goto error1;
    }

    for (indrel = 0; indrel < 2; indrel++)
    {
        if (indrel == 0)
        {
            if (dynamic_entries[DT_RELASZ] == 0) continue;
            if (dynamic_entries[DT_RELA] == 0 || dynamic_entries[DT_RELAENT] == 0) goto error1;
            relsize = dynamic_entries[DT_RELASZ];
            reladdr = dynamic_entries[DT_RELA];
        }
        else
        {
            if (dynamic_entries[DT_PLTRELSZ] == 0) continue;
            if (dynamic_entries[DT_JMPREL] == 0 || dynamic_entries[DT_RELAENT] == 0) goto error1;
            relsize = dynamic_entries[DT_PLTRELSZ];
            reladdr = dynamic_entries[DT_JMPREL];
        }

        for (section_offset = 0; section_offset < relsize; section_offset += dynamic_entries[DT_RELAENT])
        {
            relocation = (Elf64_Rela *)(library + reladdr + section_offset);
            if (((relocation->r_info & 0xffffffff) == R_X86_64_JUMP_SLOT) ||
                ((relocation->r_info & 0xffffffff) == R_AARCH64_JUMP_SLOT)
               )
            {
                if (dynamic_entries[DT_SYMTAB] == 0 || dynamic_entries[DT_SYMENT] == 0) goto error1;

                symbol = (Elf64_Sym *)(library + dynamic_entries[DT_SYMTAB] + ((uint32_t)(relocation->r_info >> 32)) * dynamic_entries[DT_SYMENT]);

                if (symbol->st_shndx == 0)
                {
                    // external symbol
                    if (symbol->st_name != 0)
                    {
                        if (dynamic_entries[DT_STRTAB] == 0) goto error1;

                        symbname = (const char *)(library + dynamic_entries[DT_STRTAB] + symbol->st_name);

                        symbvalue = NULL;
                        for (indsymb = 0; indsymb < sizeof(symbol_table)/sizeof(symbol_table[0]); indsymb++)
                        {
                            if (0 == strcmp(symbname, symbol_table[indsymb].name))
                            {
                                symbvalue = symbol_table[indsymb].value;
                                break;
                            }
                        }

                        if (symbvalue == NULL)
                        {
                            fprintf(stderr, "Error: symbol not found: %s\n", symbname);
                            goto error1;
                        }

                        *(uint64_t *)(library + relocation->r_offset) = (uintptr_t)symbvalue;
                    }
                }
                else
                {
                    // internal symbol
                    *(uint64_t *)(library + relocation->r_offset) = (uintptr_t)(library + symbol->st_value);
                }
            }
            else if (((relocation->r_info & 0xffffffff) == R_X86_64_RELATIVE) ||
                     ((relocation->r_info & 0xffffffff) == R_AARCH64_RELATIVE)
                    )
            {
                *(uint64_t *)(library + relocation->r_offset) = (uintptr_t)(library + relocation->r_addend);
            }
            else
            {
                fprintf(stderr, "Error: unsuported relocation type\n");
                goto error1;
            }
        }
    }

    // run constructors
    if (dynamic_entries[DT_INIT] != 0)
    {
        // run constructor
        ((void (*)(void)) (library + dynamic_entries[DT_INIT]))();
    }
    if (dynamic_entries[DT_INIT_ARRAYSZ] != 0)
    {
        if (dynamic_entries[DT_INIT_ARRAY] == 0) goto error1;

        for (section_offset = 0; section_offset < dynamic_entries[DT_INIT_ARRAYSZ]; section_offset += sizeof(uint64_t))
        {
            // run constructor
            ((void (*)(void))*(uint64_t *)(library + dynamic_entries[DT_INIT_ARRAY] + section_offset) )();
        }
    }

    return library;

error1:
    munmap(library, libsize);
    return NULL;
#endif
}

void *find_symbol_32bit(void *library, const char *name)
{
#ifdef _WIN32
    PIMAGE_NT_HEADERS64 nt_headers;
    PIMAGE_EXPORT_DIRECTORY export_dir;
    uint8_t *base_addr;
    uint32_t *addresses, *names;
    uint16_t *nameordinals;
    DWORD index;

    if (library == NULL || name == NULL || *name == 0) return NULL;

    nt_headers = (PIMAGE_NT_HEADERS64)library;

    base_addr = (uint8_t *)library - nt_headers->OptionalHeader.DataDirectory[15].VirtualAddress;

    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size != 0)
    {
        export_dir = (PIMAGE_EXPORT_DIRECTORY)(base_addr + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

        names = (uint32_t *)(base_addr + export_dir->AddressOfNames);

        for (index = 0; index < export_dir->NumberOfNames; index++)
        {
            if (0 == lstrcmpA(name, (const char *)(base_addr + names[index])))
            {
                addresses = (uint32_t *)(base_addr + export_dir->AddressOfFunctions);
                nameordinals = (uint16_t *)(base_addr + export_dir->AddressOfNameOrdinals);

                return base_addr + addresses[nameordinals[index]];
            }
        }
    }

    return NULL;
#else
    Elf64_Ehdr *elf_header;
    Elf64_Phdr *program_header;
    Elf64_Dyn *dynamic_entry;
    Elf64_Sym *symbol;
    const char *symbname;
    uint64_t section_offset, strtab, symtab, strsz, syment;
    int index;

    if (library == NULL || name == NULL || *name == 0) return NULL;

    elf_header = (Elf64_Ehdr *)library;

    // read dynamic entries
    strtab = symtab = strsz = syment = 0;
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(library + elf_header->e_phoff + index * elf_header->e_phentsize);

        if (program_header->p_type != PT_DYNAMIC) continue;

        for (section_offset = 0; section_offset < program_header->p_memsz; section_offset += sizeof(Elf64_Dyn))
        {
            dynamic_entry = (Elf64_Dyn *)(library + program_header->p_vaddr + section_offset);

            switch (dynamic_entry->d_tag)
            {
                case DT_STRTAB:
                    strtab = dynamic_entry->d_un.d_val;
                    break;
                case DT_SYMTAB:
                    symtab = dynamic_entry->d_un.d_val;
                    break;
                case DT_STRSZ:
                    strsz = dynamic_entry->d_un.d_val;
                    break;
                case DT_SYMENT:
                    syment = dynamic_entry->d_un.d_val;
                    break;
            }
        }
    }

    if (strtab == 0 || symtab == 0 || strsz == 0 || syment == 0) return NULL;

    for (section_offset = 0; 1; section_offset += syment)
    {
        symbol = (Elf64_Sym *)(library + symtab + section_offset);
        if (symbol->st_name >= strsz) break;

        if (symbol->st_value == 0) continue;

        symbname = (const char *)(library + strtab + symbol->st_name);

        if (0 == strcmp(name, symbname))
        {
            return library + symbol->st_value;
        }
    }

    return NULL;
#endif
}

void unload_library_32bit(void *library)
{
#ifdef _WIN32
    if (library == NULL) return;

    VirtualFree(library, 0, MEM_RELEASE);
#else
    Elf64_Ehdr *elf_header;
    Elf64_Phdr *program_header;
    Elf64_Dyn *dynamic_entry;
    int64_t page_size;
    uint64_t section_offset, fini, fini_array, fini_arraysz, max_addr;
    int index;

    if (library == NULL) return;

    // get page size
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size <= 0) page_size = 4096;

    elf_header = (Elf64_Ehdr *)library;

    // read dynamic entries
    fini = fini_array = fini_arraysz = 0;
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(library + elf_header->e_phoff + index * elf_header->e_phentsize);

        if (program_header->p_type != PT_DYNAMIC) continue;

        for (section_offset = 0; section_offset < program_header->p_memsz; section_offset += sizeof(Elf64_Dyn))
        {
            dynamic_entry = (Elf64_Dyn *)(library + program_header->p_vaddr + section_offset);

            switch (dynamic_entry->d_tag)
            {
                case DT_FINI:
                    fini = dynamic_entry->d_un.d_val;
                    break;
                case DT_FINI_ARRAY:
                    fini_array = dynamic_entry->d_un.d_val;
                    break;
                case DT_FINI_ARRAYSZ:
                    fini_arraysz = dynamic_entry->d_un.d_val;
                    break;
            }
        }
    }

    // run destructors
    if (fini != 0)
    {
        // run destructor
        ((void (*)(void)) (library + fini))();
    }
    if (fini_arraysz != 0 && fini_array != 0)
    {
        for (section_offset = 0; section_offset < fini_arraysz; section_offset += sizeof(uint64_t))
        {
            // run destructor
            ((void (*)(void))*(uint64_t *)(library + fini_array + section_offset) )();
        }
    }

    // get maximum address for unloading
    max_addr = 0;
    for (index = 0; index < elf_header->e_phnum; index++)
    {
        program_header = (Elf64_Phdr *)(elf_header->e_phoff + index * elf_header->e_phentsize + (uintptr_t)library);

        if (program_header->p_type != PT_LOAD) continue;

        if (program_header->p_vaddr + program_header->p_memsz > max_addr)
        {
            max_addr = program_header->p_vaddr + program_header->p_memsz;
        }
    }

    // align maximum address to page size
    max_addr = (max_addr + (page_size - 1)) & ~(page_size - 1);

    munmap(library, max_addr);
#endif
}

