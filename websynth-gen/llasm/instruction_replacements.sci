loc_407D01,5,;call time|mov eax, 0 ; the result isn't used for anything

loc_406A69,6,;call timeGetTime|mov eax, 0 ; the result isn't used for anything
loc_40796D,6,;call timeGetTime|mov eax, 0 ; the result isn't used for anything

loc_4049DC,4,;
loc_404A78,8,;
loc_407B04,12,;
loc_4083CC,4,;
loc_40A353,13,;

loc_40AED6,11,;
loc_40B026,11,;
loc_40B16E,5,;
loc_40B2AE,5,;
loc_40B3EE,5,;
loc_40DA98,3,;

loc_4056CE,2,;xor bl, bl|add tmp1, ecx, edx|sub tmp2, eax, ecx|cmoveq eax, tmp1, eax, tmp2, eax|mov ebx, 0 ; check if the datafile was already initialized (in another instance)
loc_405704,3,;mov edi, [ecx+0x30]|add tmpadr, ecx, 48|load edi, tmpadr, 1|add tmpadr, ecx, 40|load tmp1, tmpadr, 1|sub tmp1, tmp1, eax|ctcallnz tmp1, loc_4058CC|tcall loc_405704_1|endp|proc loc_405704_1 ; check if the datafile was already initialized (in another instance)
