loc_407D01,5,;call time|xor eax, eax ; the result isn't used for anything

loc_406A69,6,;call timeGetTime|xor eax, eax ; the result isn't used for anything
loc_40796D,6,;call timeGetTime|xor eax, eax ; the result isn't used for anything

loc_4049DC,4,align 16
loc_404A78,8,align 16
loc_407B04,12,align 16
loc_4083CC,4,align 16
loc_40A353,13,align 16

loc_40AED6,11,align 16
loc_40B026,11,align 16
loc_40B16E,5,align 16
loc_40B2AE,5,align 16
loc_40B3EE,5,align 16
loc_40DA98,3,align 16

loc_4056CE,2,lea ebx, [ecx+edx]|cmp eax, ebx|jne short loc_4056CE_1|sub eax, ecx|loc_4056CE_1:|xor bl, bl ; check if the datafile was already initialized (in another instance)
loc_405704,3,mov edi, [ecx+0x30]|cmp eax, [ecx+0x28]|jne loc_4058CC ; check if the datafile was already initialized (in another instance)
