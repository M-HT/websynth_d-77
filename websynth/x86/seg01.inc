align 16
loc_401000:
push ecx
push ebx
push esi
push edi
mov eax, loc_41FEB8
mov [esp+0xc], ecx
xor edi, edi
mov [loc_41FEBC], eax
mov [loc_41FEB8], eax
mov [loc_41FF18], edi
mov dword [loc_41FEB4], loc_41FEB0
mov esi, loc_41FEB0
xor ebx, ebx
mov eax, loc_41E6C4
mov cl, 0xff
loc_401037:
lea edx, [eax-0x14]
mov [eax-0xc], edi
mov [eax], edi
mov [eax+0x18], bl
mov [edx], esi
mov [esi+0x4], edx
mov dword [eax-0x10], loc_41FEB0
mov [eax-0x4], edi
mov byte [eax+0x5], 0x1
mov [eax-0x8], edi
mov [eax+0x6], cl
add eax, 0x30
inc ebx
cmp eax, loc_41FEC4
mov esi, edx
jl short loc_401037
mov ecx, [esp+0xc]
mov [loc_41FEB0], esi
call loc_401FE0
pop edi
pop esi
pop ebx
pop ecx
ret
align 16
loc_401080:
sub esp, 0x1c
push ebx
push ebp
push esi
mov ebx, edx
push edi
mov edi, ebx
and edi, 0xff
mov esi, ecx
mov eax, edi
mov ecx, edi
shr eax, 0x3
and ecx, 0x7
mov [esp+0x14], ebx
lea eax, [eax+esi+0x61]
mov dword [esp+0x18], 0x1
mov dl, [ecx+loc_41B030]
mov byte [esp+0x13], 0xff
mov cl, [eax]
mov [esp+0x1c], edi
or cl, dl
mov [eax], cl
mov dl, [esi+0x5f]
inc dl
mov ecx, esi
mov [esi+0x5f], dl
mov dl, bl
call loc_405C80
test eax, eax
mov [esp+0x20], eax
jz short loc_4010F3
mov ecx, [esp+0x30]
lea edx, [esp+0x24]
push ecx
mov ecx, eax
call loc_405CC0
mov eax, [esp+0x24]
test eax, eax
jnz short loc_40110D
loc_4010F3:
mov al, [edi+esi+0x81]
inc al
mov [edi+esi+0x81], al
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x1c
ret 0x4
loc_40110D:
mov eax, [esi+0x1c]
test eax, eax
jz near loc_401246
mov al, [eax+edi+0x3]
mov [esp+0x13], al
mov bl, al
mov al, [esi+0x57]
and bl, 0x7f
test al, al
jz near loc_4011D9
mov ecx, [esi+0x10]
lea ebp, [esi+0x10]
cmp ecx, ebp
jz short loc_401162
loc_40113A:
cmp [ecx+0x1a], bl
jnz short loc_40115C
mov edx, [ecx]
mov edi, [ecx+0x4]
mov [edx+0x4], edi
mov eax, [ecx+0x4]
mov edx, [ecx]
mov [eax], edx
call loc_401900
mov al, [esi+0x57]
test al, al
jz short loc_4011D9
mov ecx, edi
loc_40115C:
mov ecx, [ecx]
cmp ecx, ebp
jnz short loc_40113A
loc_401162:
mov ecx, [esi+0x8]
lea ebp, [esi+0x8]
cmp ecx, ebp
jz short loc_401194
loc_40116C:
cmp [ecx+0x1a], bl
jnz short loc_40118E
mov eax, [ecx]
mov edi, [ecx+0x4]
mov [eax+0x4], edi
mov edx, [ecx+0x4]
mov eax, [ecx]
mov [edx], eax
call loc_401900
mov al, [esi+0x57]
test al, al
jz short loc_4011D9
mov ecx, edi
loc_40118E:
mov ecx, [ecx]
cmp ecx, ebp
jnz short loc_40116C
loc_401194:
mov ecx, [esi]
cmp ecx, esi
jz short loc_4011D9
loc_40119A:
cmp [ecx+0x1a], bl
jnz short loc_4011D3
mov edx, [ecx]
mov edi, [ecx+0x4]
mov [edx+0x4], edi
mov eax, [ecx+0x4]
mov edx, [ecx]
mov [eax], edx
xor eax, eax
mov al, [ecx+0x18]
mov dl, [eax+esi+0x81]
lea eax, [eax+esi+0x81]
inc dl
mov [eax], dl
call loc_401900
mov al, [esi+0x57]
test al, al
jz short loc_4011D9
mov ecx, edi
loc_4011D3:
mov ecx, [ecx]
cmp ecx, esi
jnz short loc_40119A
loc_4011D9:
mov ebx, [esp+0x14]
loc_4011DD:
mov edi, [loc_41FEB4]
cmp edi, loc_41FEB0
jz short loc_401207
mov ecx, [edi+0x4]
lea eax, [edi+0x4]
mov [loc_41FEB4], ecx
mov edx, [eax]
test edi, edi
mov dword [edx], loc_41FEB0
jnz near loc_401354
loc_401207:
mov dword [esp+0x18], 0x0
call loc_4019E0
call loc_401A40
call loc_401AD0
mov edi, eax
test edi, edi
jnz near loc_401354
mov eax, [esp+0x1c]
pop edi
mov cl, [eax+esi+0x81]
inc cl
mov [eax+esi+0x81], cl
pop esi
pop ebp
pop ebx
add esp, 0x1c
ret 0x4
loc_401246:
xor eax, eax
mov al, [esi+0x5a]
sub eax, 0x0
jz short loc_4012A2
dec eax
jnz short loc_4011DD
mov dl, bl
lea ecx, [esi+0x10]
call loc_401FB0
test eax, eax
jnz short loc_401287
mov dl, bl
lea ecx, [esi+0x8]
call loc_401FB0
test eax, eax
jnz short loc_401287
mov dl, bl
mov ecx, esi
call loc_401FB0
test eax, eax
jz near loc_4011DD
inc byte [edi+esi+0x81]
loc_401287:
mov ecx, [eax]
mov edx, [eax+0x4]
mov [ecx+0x4], edx
mov ecx, [eax+0x4]
mov edx, [eax]
mov [ecx], edx
mov ecx, eax
call loc_401900
jmp loc_4011DD
loc_4012A2:
mov al, [esi+0x57]
test al, al
jz near loc_4011DD
mov ecx, [esi+0x10]
lea ebp, [esi+0x10]
cmp ecx, ebp
jz short loc_4012E3
loc_4012B7:
cmp [ecx+0x18], bl
jnz short loc_4012DD
mov eax, [ecx]
mov edi, [ecx+0x4]
mov [eax+0x4], edi
mov edx, [ecx+0x4]
mov eax, [ecx]
mov [edx], eax
call loc_401900
mov al, [esi+0x57]
test al, al
jz near loc_4011DD
mov ecx, edi
loc_4012DD:
mov ecx, [ecx]
cmp ecx, ebp
jnz short loc_4012B7
loc_4012E3:
mov ecx, [esi+0x8]
lea ebp, [esi+0x8]
cmp ecx, ebp
jz short loc_401319
loc_4012ED:
cmp [ecx+0x18], bl
jnz short loc_401313
mov edx, [ecx]
mov edi, [ecx+0x4]
mov [edx+0x4], edi
mov eax, [ecx+0x4]
mov edx, [ecx]
mov [eax], edx
call loc_401900
mov al, [esi+0x57]
test al, al
jz near loc_4011DD
mov ecx, edi
loc_401313:
mov ecx, [ecx]
cmp ecx, ebp
jnz short loc_4012ED
loc_401319:
mov ecx, [esi]
cmp ecx, esi
jz near loc_4011DD
loc_401323:
cmp [ecx+0x18], bl
jnz short loc_401349
mov eax, [ecx]
mov edi, [ecx+0x4]
mov [eax+0x4], edi
mov edx, [ecx+0x4]
mov eax, [ecx]
mov [edx], eax
call loc_401900
mov al, [esi+0x57]
test al, al
jz near loc_4011DD
mov ecx, edi
loc_401349:
mov ecx, [ecx]
cmp ecx, esi
jnz short loc_401323
jmp loc_4011DD
loc_401354:
mov ebp, [esp+0x20]
mov al, [esp+0x13]
mov [edi+0x14], ebp
mov dword [edi+0x8], 0x0
mov [edi+0xc], esi
mov [edi+0x18], bl
mov [edi+0x1a], al
mov eax, [esp+0x28]
test eax, eax
jz short loc_4013EC
call loc_4019B0
test eax, eax
mov [edi+0x8], eax
jnz short loc_4013C6
mov eax, [esp+0x18]
test eax, eax
jz short loc_401390
call loc_4019E0
loc_401390:
call loc_401A40
call loc_401AD0
test eax, eax
mov [edi+0x8], eax
jnz short loc_4013C6
mov eax, [esp+0x1c]
mov cl, [eax+esi+0x81]
inc cl
mov [eax+esi+0x81], cl
mov ecx, edi
call loc_401980
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x1c
ret 0x4
loc_4013C6:
mov ecx, [edi+0x8]
mov [ecx+0x14], ebp
mov edx, [edi+0x8]
mov dword [edx+0x8], 0x0
mov eax, [edi+0x8]
mov [eax+0xc], esi
mov ecx, [edi+0x8]
mov al, [esp+0x13]
mov [ecx+0x18], bl
mov edx, [edi+0x8]
mov [edx+0x1a], al
loc_4013EC:
mov ecx, [esi]
mov [edi], ecx
mov [esi], edi
mov edx, [edi]
lea ecx, [esp+0x24]
mov [edx+0x4], edi
mov [edi+0x4], esi
mov byte [edi+0x19], 0x2
mov al, [esi+0x57]
inc al
mov edx, edi
mov [esi+0x57], al
mov eax, [esp+0x30]
push eax
push ebx
push ecx
mov ecx, esi
call loc_408CB0
xor edx, edx
mov dl, [edi+0x2c]
pop edi
pop esi
pop ebp
mov byte [edx+loc_455F68], 0x1
mov dword [loc_41B6F8], 0x0
pop ebx
add esp, 0x1c
ret 0x4
align 16
loc_401440:
push ebx
push esi
mov esi, edx
push edi
and esi, 0xff
mov edi, esi
mov eax, esi
shr edi, 0x3
and eax, 0x7
mov bl, [edi+ecx+0x61]
lea edi, [edi+ecx+0x61]
mov al, [eax+loc_41B030]
test al, bl
jz short loc_401481
mov bl, [edi+0x10]
add edi, 0x10
test al, bl
jnz short loc_401481
or bl, al
mov [edi], bl
mov al, [ecx+0x60]
inc al
pop edi
pop esi
mov [ecx+0x60], al
pop ebx
ret
loc_401481:
mov al, [esi+ecx+0x81]
test al, al
jz short loc_401499
dec al
pop edi
mov [esi+ecx+0x81], al
pop esi
pop ebx
ret
loc_401499:
mov eax, [ecx+0x4]
cmp eax, ecx
jz near loc_401580
loc_4014A4:
cmp [eax+0x18], dl
jz short loc_4014B4
mov eax, [eax+0x4]
cmp eax, ecx
jnz short loc_4014A4
pop edi
pop esi
pop ebx
ret
loc_4014B4:
mov edx, [eax]
mov esi, [eax+0x4]
mov [edx+0x4], esi
mov edx, [eax+0x4]
mov esi, [eax]
mov [edx], esi
xor edx, edx
mov dl, [eax+0x2c]
mov esi, edx
mov dl, 0x1
mov bl, [esi+loc_455F68]
cmp bl, dl
jz short loc_401507
mov dl, [ecx+0x59]
test dl, dl
jz short loc_4014E2
add ecx, 0x8
jmp short loc_4014F3
loc_4014E2:
test bl, bl
setnz dl
add edx, 0x2
add ecx, 0x10
mov [esi+loc_455F68], dl
loc_4014F3:
mov byte [eax+0x19], 0x3
mov edx, [ecx]
mov [eax], edx
pop edi
mov [edx+0x4], eax
mov [ecx], eax
pop esi
mov [eax+0x4], ecx
pop ebx
ret
loc_401507:
mov esi, [eax+0xc]
mov cl, [esi+0x57]
test cl, cl
jz short loc_401516
dec cl
mov [esi+0x57], cl
loc_401516:
mov ecx, [loc_41FEB0]
mov edi, loc_41FEB0
mov [eax], ecx
mov ecx, [loc_41FEB0]
xor esi, esi
mov [ecx+0x4], eax
xor ecx, ecx
mov [loc_41FEB0], eax
mov cl, [eax+0x2c]
mov [eax+0x4], edi
mov [eax+0x10], esi
mov [eax+0x19], dl
mov [eax+0xc], esi
mov byte [eax+0x1a], 0xff
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, esi
jz short loc_401580
mov ebx, [loc_41FEB0]
mov [ecx], ebx
mov ebx, [loc_41FEB0]
mov [ebx+0x4], ecx
mov [loc_41FEB0], ecx
mov [ecx+0x4], edi
mov [ecx+0x10], esi
mov [ecx+0x19], dl
mov [ecx+0xc], esi
mov byte [ecx+0x1a], 0xff
mov [eax+0x8], esi
loc_401580:
pop edi
pop esi
pop ebx
ret
align 16
loc_401590:
cmp dl, 0x40
push esi
jb short loc_40159C
mov byte [ecx+0x59], 0x1
pop esi
ret
loc_40159C:
lea edx, [ecx+0x8]
mov byte [ecx+0x59], 0x0
lea esi, [ecx+0x10]
mov eax, [edx+0x4]
cmp eax, edx
jz short loc_4015E6
loc_4015AD:
mov ecx, [eax+0x4]
mov [edx+0x4], ecx
mov ecx, [eax+0x4]
mov [ecx], edx
mov ecx, [esi]
mov [eax], ecx
mov [ecx+0x4], eax
xor ecx, ecx
mov [esi], eax
mov cl, [eax+0x2c]
mov [eax+0x4], esi
mov eax, ecx
mov cl, [eax+loc_455F68]
test cl, cl
setnz cl
add ecx, 0x2
mov [eax+loc_455F68], cl
mov eax, [edx+0x4]
cmp eax, edx
jnz short loc_4015AD
loc_4015E6:
pop esi
ret
align 16
loc_4015F0:
push esi
mov esi, ecx
xor al, al
cmp [esi+0x5f], al
jz short loc_401624
mov [esi+0x5f], al
mov edx, [loc_42A2E8]
lea ecx, [esi+0x61]
mov [esi+0x61], edx
mov edx, [loc_42A2EC]
mov [ecx+0x4], edx
mov edx, [loc_42A2F0]
mov [ecx+0x8], edx
mov edx, [loc_42A2F4]
mov [ecx+0xc], edx
loc_401624:
cmp [esi+0x60], al
jz short loc_401653
mov [esi+0x60], al
mov ecx, [loc_42A2E8]
lea eax, [esi+0x71]
mov [esi+0x71], ecx
mov edx, [loc_42A2EC]
mov [eax+0x4], edx
mov ecx, [loc_42A2F0]
mov [eax+0x8], ecx
mov edx, [loc_42A2F4]
mov [eax+0xc], edx
loc_401653:
push edi
mov ecx, 0x20
xor eax, eax
lea edi, [esi+0x81]
rep stosd
mov eax, [esi]
pop edi
cmp eax, esi
jz short loc_40167A
loc_40166A:
mov dl, [eax+0x18]
mov ecx, esi
call loc_401440
mov eax, [esi]
cmp eax, esi
jnz short loc_40166A
loc_40167A:
pop esi
ret
align 16
loc_401680:
sub esp, 0x14
xor edx, edx
push ebx
push ebp
push esi
mov esi, ecx
push edi
cmp [esi+0x5f], dl
jz short loc_4016BA
mov [esi+0x5f], dl
mov ecx, [loc_42A2E8]
lea eax, [esi+0x61]
mov [esi+0x61], ecx
mov ecx, [loc_42A2EC]
mov [eax+0x4], ecx
mov ecx, [loc_42A2F0]
mov [eax+0x8], ecx
mov ecx, [loc_42A2F4]
mov [eax+0xc], ecx
loc_4016BA:
cmp [esi+0x60], dl
jz short loc_4016E9
mov [esi+0x60], dl
mov ecx, [loc_42A2E8]
lea eax, [esi+0x71]
mov [esi+0x71], ecx
mov ecx, [loc_42A2EC]
mov [eax+0x4], ecx
mov ecx, [loc_42A2F0]
mov [eax+0x8], ecx
mov ecx, [loc_42A2F4]
mov [eax+0xc], ecx
loc_4016E9:
mov ecx, 0x20
xor eax, eax
lea edi, [esi+0x81]
mov [esp+0x18], esi
rep stosd
lea eax, [esi+0x8]
add esi, 0x10
lea ecx, [esp+0x20]
mov [esp+0x1c], eax
mov [esp+0x20], esi
mov [esp+0x10], ecx
mov dword [esp+0x14], 0x3
mov ebp, loc_41FEB0
mov bl, 0xff
loc_401721:
mov eax, [esp+0x10]
mov edi, [eax]
mov eax, [edi+0x4]
cmp eax, edi
jz near loc_4017BA
loc_401732:
mov ecx, [eax+0x4]
mov [edi+0x4], ecx
mov ecx, [eax+0x4]
mov [ecx], edi
mov esi, [eax+0xc]
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_40174C
dec cl
mov [esi+0x57], cl
loc_40174C:
mov ecx, [loc_41FEB0]
mov [eax], ecx
mov ecx, [loc_41FEB0]
mov [ecx+0x4], eax
xor ecx, ecx
mov [loc_41FEB0], eax
mov cl, [eax+0x2c]
mov [eax+0x4], ebp
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz short loc_4017AF
mov esi, [loc_41FEB0]
mov [ecx], esi
mov esi, [loc_41FEB0]
mov [esi+0x4], ecx
mov [loc_41FEB0], ecx
mov [ecx+0x4], ebp
mov [ecx+0x10], edx
mov byte [ecx+0x19], 0x1
mov [ecx+0xc], edx
mov [ecx+0x1a], bl
mov [eax+0x8], edx
loc_4017AF:
mov eax, [edi+0x4]
cmp eax, edi
jnz near loc_401732
loc_4017BA:
mov eax, [esp+0x14]
mov esi, [esp+0x10]
dec eax
sub esi, 0x4
cmp eax, edx
mov [esp+0x14], eax
mov [esp+0x10], esi
ja near loc_401721
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x14
ret
align 16
loc_4017E0:
lea eax, [ecx+ecx*2]
push esi
shl eax, 0x4
add eax, loc_41E6B0
cmp [eax+0x10], edx
jnz near loc_401895
xor ecx, ecx
mov cl, [eax+0x19]
sub ecx, 0x2
jz short loc_401804
dec ecx
jz short loc_401815
pop esi
ret
loc_401804:
mov edx, [eax+0xc]
xor ecx, ecx
mov cl, [eax+0x18]
lea ecx, [ecx+edx+0x81]
inc byte [ecx]
loc_401815:
mov ecx, [eax]
mov edx, [eax+0x4]
mov [ecx+0x4], edx
mov ecx, [eax+0x4]
mov edx, [eax]
mov [ecx], edx
mov esi, [eax+0xc]
xor edx, edx
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401835
dec cl
mov [esi+0x57], cl
loc_401835:
mov ecx, [loc_41FEB0]
mov esi, loc_41FEB0
mov [eax], ecx
mov ecx, [loc_41FEB0]
mov [ecx+0x4], eax
mov [loc_41FEB0], eax
mov ecx, [eax+0x8]
mov [eax+0x4], esi
cmp ecx, edx
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov byte [eax+0x1a], 0xff
jz short loc_401895
push edi
mov edi, [loc_41FEB0]
mov [ecx], edi
mov edi, [loc_41FEB0]
mov [edi+0x4], ecx
mov [loc_41FEB0], ecx
mov [ecx+0x4], esi
mov [ecx+0x10], edx
mov byte [ecx+0x19], 0x1
mov [ecx+0xc], edx
mov byte [ecx+0x1a], 0xff
mov [eax+0x8], edx
pop edi
loc_401895:
pop esi
ret
align 16
loc_4018A0:
lea ecx, [ecx+ecx*2]
shl ecx, 0x4
add ecx, loc_41E6B0
cmp [ecx+0x10], edx
jnz short loc_4018F5
mov al, [ecx+0x19]
cmp al, 0x2
jb short loc_4018F5
cmp al, 0x3
ja short loc_4018F5
mov eax, [ecx+0x8]
xor edx, edx
cmp eax, edx
jz short loc_4018F5
push esi
mov esi, [loc_41FEB0]
mov [eax], esi
mov esi, [loc_41FEB0]
mov [esi+0x4], eax
mov [loc_41FEB0], eax
mov dword [eax+0x4], loc_41FEB0
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov byte [eax+0x1a], 0xff
mov [ecx+0x8], edx
pop esi
loc_4018F5:
ret 0x4
align 16
loc_401900:
push esi
mov esi, [ecx+0xc]
xor edx, edx
mov al, [esi+0x57]
cmp al, dl
jz short loc_401912
dec al
mov [esi+0x57], al
loc_401912:
mov eax, [loc_41FEB0]
mov esi, loc_41FEB0
mov [ecx], eax
mov eax, [loc_41FEB0]
mov [eax+0x4], ecx
xor eax, eax
mov [loc_41FEB0], ecx
mov al, [ecx+0x2c]
mov [ecx+0x4], esi
mov [ecx+0x10], edx
mov byte [ecx+0x19], 0x1
mov [ecx+0xc], edx
mov byte [ecx+0x1a], 0xff
mov byte [eax+loc_455F68], 0x3
mov eax, [ecx+0x8]
cmp eax, edx
jz short loc_40197C
push edi
mov edi, [loc_41FEB0]
mov [eax], edi
mov edi, [loc_41FEB0]
mov [edi+0x4], eax
mov [loc_41FEB0], eax
mov [eax+0x4], esi
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov byte [eax+0x1a], 0xff
mov [ecx+0x8], edx
pop edi
loc_40197C:
pop esi
ret
align 16
loc_401980:
mov eax, [loc_41FEB0]
mov [ecx], eax
mov edx, [loc_41FEB0]
xor eax, eax
mov [edx+0x4], ecx
mov [loc_41FEB0], ecx
mov dword [ecx+0x4], loc_41FEB0
mov [ecx+0x10], eax
mov byte [ecx+0x19], 0x1
mov [ecx+0xc], eax
mov byte [ecx+0x1a], 0xff
ret
align 16
loc_4019B0:
mov eax, [loc_41FEB4]
cmp eax, loc_41FEB0
jz short loc_4019D1
mov edx, [eax+0x4]
lea ecx, [eax+0x4]
mov [loc_41FEB4], edx
mov ecx, [ecx]
mov dword [ecx], loc_41FEB0
ret
loc_4019D1:
xor eax, eax
ret
align 16
loc_4019E0:
push ebp
push esi
push edi
xor esi, esi
mov ecx, loc_42A95F
mov edi, loc_41FED0
mov ebp, 0x10
loc_4019F4:
mov al, [ecx]
mov dl, [ecx+0x1]
cmp al, dl
jbe short loc_401A0E
sub al, dl
mov [esi+loc_41FEC0], al
lea eax, [ecx-0x57]
mov [edi], eax
inc esi
add edi, 0x4
loc_401A0E:
add ecx, 0x104
dec ebp
jnz short loc_4019F4
mov byte [esi+loc_41FEC0], 0x0
mov dword [esi*4+loc_41FED0], 0x0
pop edi
pop esi
mov dword [loc_41FF10], 0x0
pop ebp
ret
align 16
loc_401A40:
push ecx
mov ecx, [loc_41FF10]
push ebp
mov [esp+0x4], ecx
mov dl, [ecx+loc_41FEC0]
lea ebp, [ecx+loc_41FEC0]
test dl, dl
jz short loc_401AC7
push ebx
push esi
push edi
lea esi, [ecx*4+loc_41FED0]
loc_401A66:
mov al, [ecx+loc_41FEC1]
mov ebx, [esi]
lea edi, [ecx+loc_41FEC1]
test al, al
jz short loc_401AA3
lea ecx, [esi+0x4]
loc_401A7B:
cmp al, dl
ja short loc_401A85
jb short loc_401A94
cmp [ecx], ebx
jbe short loc_401A94
loc_401A85:
mov [ebp], al
mov [edi], dl
mov dl, al
mov eax, [ecx]
mov [esi], eax
mov [ecx], ebx
mov ebx, [esi]
loc_401A94:
mov al, [edi+0x1]
add ecx, 0x4
inc edi
test al, al
jnz short loc_401A7B
mov ecx, [esp+0x10]
loc_401AA3:
inc ecx
add esi, 0x4
mov [esp+0x10], ecx
mov dl, [ecx+loc_41FEC0]
lea ebp, [ecx+loc_41FEC0]
test dl, dl
jnz short loc_401A66
pop edi
pop esi
pop ebx
mov [loc_41FF10], ecx
pop ebp
pop ecx
ret
loc_401AC7:
mov [loc_41FF10], ecx
pop ebp
pop ecx
ret
loc_401AD0:
push ebx
mov bl, [loc_41FEC0]
push ebp
push esi
push edi
xor edx, edx
xor edi, edi
cmp bl, dl
jz short loc_401B06
mov ecx, loc_41FED0
loc_401AE7:
mov esi, [ecx]
cmp [esi+0x1c], edx
jnz short loc_401AF8
mov eax, [esi+0x14]
lea ebp, [esi+0x10]
cmp eax, ebp
jnz short loc_401B38
loc_401AF8:
mov al, [edi+loc_41FEC1]
inc edi
add ecx, 0x4
cmp al, dl
jnz short loc_401AE7
loc_401B06:
xor edi, edi
cmp bl, dl
jz near loc_401C3A
mov ecx, loc_41FED0
loc_401B15:
mov esi, [ecx]
mov eax, [esi+0xc]
lea ebp, [esi+0x8]
cmp eax, ebp
jnz near loc_401BB9
mov al, [edi+loc_41FEC1]
inc edi
add ecx, 0x4
cmp al, dl
jnz short loc_401B15
jmp loc_401C3A
loc_401B38:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401B44
dec cl
mov [esi+0x57], cl
loc_401B44:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jnz near loc_401D68
mov cl, [edi+loc_41FEC0]
dec cl
mov [edi+loc_41FEC0], cl
jnz short loc_401BAE
mov cl, [edi+loc_41FEC1]
lea esi, [edi+loc_41FEC1]
mov ebp, esi
inc esi
cmp cl, dl
mov [edi+loc_41FEC0], cl
jz short loc_401BAE
loc_401BA2:
mov cl, [esi]
inc edi
mov [ebp], cl
inc ebp
inc esi
cmp cl, dl
jnz short loc_401BA2
loc_401BAE:
mov [loc_41FF10], edi
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401BB9:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401BC5
dec cl
mov [esi+0x57], cl
loc_401BC5:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jnz near loc_401D68
mov cl, [edi+loc_41FEC0]
dec cl
mov [edi+loc_41FEC0], cl
jnz short loc_401C2F
mov cl, [edi+loc_41FEC1]
lea esi, [edi+loc_41FEC1]
mov ebp, esi
inc esi
cmp cl, dl
mov [edi+loc_41FEC0], cl
jz short loc_401C2F
loc_401C23:
mov cl, [esi]
inc edi
mov [ebp], cl
inc ebp
inc esi
cmp cl, dl
jnz short loc_401C23
loc_401C2F:
mov [loc_41FF10], edi
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401C3A:
xor edi, edi
cmp bl, dl
jz short loc_401C64
mov ecx, loc_41FED0
loc_401C45:
mov esi, [ecx]
cmp [esi+0x1c], edx
jz short loc_401C56
mov eax, [esi+0x14]
lea ebp, [esi+0x10]
cmp eax, ebp
jnz short loc_401C93
loc_401C56:
mov al, [edi+loc_41FEC1]
inc edi
add ecx, 0x4
cmp al, dl
jnz short loc_401C45
loc_401C64:
xor edi, edi
cmp bl, dl
jz near loc_401DDB
mov ecx, loc_41FED0
loc_401C73:
mov esi, [ecx]
mov eax, [esi+0x4]
cmp eax, esi
jnz near loc_401D14
mov al, [edi+loc_41FEC1]
inc edi
add ecx, 0x4
cmp al, dl
jnz short loc_401C73
jmp loc_401DDB
loc_401C93:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401C9F
dec cl
mov [esi+0x57], cl
loc_401C9F:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jnz near loc_401D68
mov cl, [edi+loc_41FEC0]
dec cl
mov [edi+loc_41FEC0], cl
jnz short loc_401D09
mov cl, [edi+loc_41FEC1]
lea esi, [edi+loc_41FEC1]
mov ebp, esi
inc esi
cmp cl, dl
mov [edi+loc_41FEC0], cl
jz short loc_401D09
loc_401CFD:
mov cl, [esi]
inc edi
mov [ebp], cl
inc ebp
inc esi
cmp cl, dl
jnz short loc_401CFD
loc_401D09:
mov [loc_41FF10], edi
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401D14:
xor ecx, ecx
mov cl, [eax+0x18]
mov bl, [ecx+esi+0x81]
lea ecx, [ecx+esi+0x81]
inc bl
mov [ecx], bl
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401D37
dec cl
mov [esi+0x57], cl
loc_401D37:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz short loc_401D9B
loc_401D68:
mov esi, [loc_41FEB0]
pop edi
mov [ecx], esi
mov esi, [loc_41FEB0]
mov [esi+0x4], ecx
mov [loc_41FEB0], ecx
mov dword [ecx+0x4], loc_41FEB0
mov [ecx+0x10], edx
mov byte [ecx+0x19], 0x1
mov [ecx+0xc], edx
pop esi
mov [ecx+0x1a], bl
pop ebp
mov [eax+0x8], edx
pop ebx
ret
loc_401D9B:
mov cl, [edi+loc_41FEC0]
dec cl
mov [edi+loc_41FEC0], cl
jnz short loc_401DD0
mov cl, [edi+loc_41FEC1]
lea esi, [edi+loc_41FEC1]
mov ebp, esi
inc esi
cmp cl, dl
mov [edi+loc_41FEC0], cl
jz short loc_401DD0
loc_401DC4:
mov cl, [esi]
inc edi
mov [ebp], cl
inc ebp
inc esi
cmp cl, dl
jnz short loc_401DC4
loc_401DD0:
mov [loc_41FF10], edi
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401DDB:
mov esi, loc_42B844
mov ecx, 0xf
loc_401DE5:
cmp [esi+0x1c], edx
jnz short loc_401DF9
cmp [esi+0x57], dl
jz short loc_401DF9
mov eax, [esi+0x14]
lea edi, [esi+0x10]
cmp eax, edi
jnz short loc_401E31
loc_401DF9:
sub esi, 0x104
mov eax, ecx
dec ecx
test eax, eax
jnz short loc_401DE5
mov esi, loc_42B844
mov ecx, 0xf
loc_401E10:
cmp [esi+0x57], dl
jz short loc_401E1F
mov eax, [esi+0xc]
lea edi, [esi+0x8]
cmp eax, edi
jnz short loc_401E77
loc_401E1F:
sub esi, 0x104
mov eax, ecx
dec ecx
test eax, eax
jnz short loc_401E10
jmp loc_401EBD
loc_401E31:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401E3D
dec cl
mov [esi+0x57], cl
loc_401E3D:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz near loc_401FAB
jmp loc_401D68
loc_401E77:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401E83
dec cl
mov [esi+0x57], cl
loc_401E83:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz near loc_401FAB
jmp loc_401D68
loc_401EBD:
mov esi, loc_42B844
mov ecx, 0xf
loc_401EC7:
cmp [esi+0x1c], edx
jz short loc_401EDB
cmp [esi+0x57], dl
jz short loc_401EDB
mov eax, [esi+0x14]
lea edi, [esi+0x10]
cmp eax, edi
jnz short loc_401F10
loc_401EDB:
sub esi, 0x104
mov eax, ecx
dec ecx
test eax, eax
jnz short loc_401EC7
mov esi, loc_42B844
mov ecx, 0xf
loc_401EF2:
cmp [esi+0x57], dl
jz short loc_401EFE
mov eax, [esi+0x4]
cmp eax, esi
jnz short loc_401F52
loc_401EFE:
sub esi, 0x104
mov eax, ecx
dec ecx
test eax, eax
jnz short loc_401EF2
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401F10:
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401F1C
dec cl
mov [esi+0x57], cl
loc_401F1C:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz short loc_401FAB
jmp loc_401D68
loc_401F52:
xor ecx, ecx
mov cl, [eax+0x18]
mov bl, [ecx+esi+0x81]
lea ecx, [ecx+esi+0x81]
inc bl
mov [ecx], bl
mov cl, [esi+0x57]
cmp cl, dl
jz short loc_401F75
dec cl
mov [esi+0x57], cl
loc_401F75:
mov ecx, [eax]
mov esi, [eax+0x4]
mov bl, 0xff
mov [ecx+0x4], esi
mov ecx, [eax+0x4]
mov esi, [eax]
mov [ecx], esi
xor ecx, ecx
mov cl, [eax+0x2c]
mov [eax+0x10], edx
mov byte [eax+0x19], 0x1
mov [eax+0xc], edx
mov [eax+0x1a], bl
mov byte [ecx+loc_455F68], 0x3
mov ecx, [eax+0x8]
cmp ecx, edx
jz short loc_401FAB
jmp loc_401D68
loc_401FAB:
pop edi
pop esi
pop ebp
pop ebx
ret
loc_401FB0:
push esi
mov esi, [ecx]
push edi
xor eax, eax
xor edi, edi
cmp esi, ecx
jz short loc_401FD4
loc_401FBC:
cmp [esi+0x18], dl
jnz short loc_401FCE
test edi, edi
jz short loc_401FC9
mov eax, esi
jmp short loc_401FCE
loc_401FC9:
mov edi, 0x1
loc_401FCE:
mov esi, [esi]
cmp esi, ecx
jnz short loc_401FBC
loc_401FD4:
pop edi
pop esi
ret
align 16
loc_401FE0:
push ecx
cmp ecx, 0x80
jbe short loc_401FEE
mov ecx, 0x80
loc_401FEE:
push edi
mov edi, 0x80
sub edi, ecx
cmp edi, 0x7c
mov [esp+0x4], edi
jle short loc_40200B
mov dword [esp+0x4], 0x7c
mov edi, [esp+0x4]
loc_40200B:
mov ecx, [loc_41FF18]
push ebx
push ebp
cmp edi, ecx
push esi
jle near loc_402141
loc_40201C:
mov eax, [loc_41FEB4]
cmp eax, loc_41FEB0
jz short loc_402044
mov edx, [eax+0x4]
lea ecx, [eax+0x4]
mov [loc_41FEB4], edx
mov ecx, [ecx]
test eax, eax
mov dword [ecx], loc_41FEB0
jnz near loc_4020F7
loc_402044:
xor esi, esi
mov ecx, loc_42A95F
mov ebp, loc_41FED0
mov ebx, 0x10
loc_402055:
mov al, [ecx]
mov dl, [ecx+0x1]
cmp al, dl
jbe short loc_402070
sub al, dl
lea edx, [ecx-0x57]
mov [esi+loc_41FEC0], al
mov [ebp], edx
inc esi
add ebp, 0x4
loc_402070:
add ecx, 0x104
dec ebx
jnz short loc_402055
mov byte [esi+loc_41FEC0], 0x0
mov dl, [loc_41FEC0]
xor ebx, ebx
test dl, dl
mov [esi*4+loc_41FED0], ebx
jz short loc_4020E8
mov esi, loc_41FED0
loc_402098:
mov al, [ebx+loc_41FEC1]
mov ebp, [esi]
lea ecx, [ebx+loc_41FEC1]
test al, al
jz short loc_4020DA
mov edi, ecx
lea ecx, [esi+0x4]
loc_4020AF:
cmp al, dl
ja short loc_4020B9
jb short loc_4020CB
cmp [ecx], ebp
jbe short loc_4020CB
loc_4020B9:
mov [ebx+loc_41FEC0], al
mov [edi], dl
mov dl, al
mov eax, [ecx]
mov [esi], eax
mov [ecx], ebp
mov ebp, [esi]
loc_4020CB:
mov al, [edi+0x1]
add ecx, 0x4
inc edi
test al, al
jnz short loc_4020AF
mov edi, [esp+0x10]
loc_4020DA:
mov dl, [ebx+loc_41FEC1]
inc ebx
add esi, 0x4
test dl, dl
jnz short loc_402098
loc_4020E8:
mov [loc_41FF10], ebx
call loc_401AD0
test eax, eax
jz short loc_40213B
loc_4020F7:
mov ecx, [loc_41FEB8]
mov [eax], ecx
mov edx, [loc_41FEB8]
xor ecx, ecx
mov [edx+0x4], eax
mov [loc_41FEB8], eax
mov dword [eax+0x4], loc_41FEB8
mov [eax+0x10], ecx
mov byte [eax+0x19], 0x1
mov [eax+0xc], ecx
mov byte [eax+0x1a], 0xff
mov ecx, [loc_41FF18]
inc ecx
cmp edi, ecx
mov [loc_41FF18], ecx
jg near loc_40201C
jmp short loc_402141
loc_40213B:
mov ecx, [loc_41FF18]
loc_402141:
pop esi
pop ebp
cmp edi, ecx
pop ebx
jge short loc_4021A4
mov edx, loc_41FEB0
loc_40214D:
mov eax, [loc_41FEB8]
cmp eax, loc_41FEB8
jz short loc_4021A4
mov ecx, [eax]
mov dword [ecx+0x4], loc_41FEB8
mov ecx, [eax]
mov [loc_41FEB8], ecx
mov ecx, [loc_41FEB0]
mov [eax], ecx
mov ecx, [loc_41FEB0]
mov [ecx+0x4], eax
xor ecx, ecx
mov [loc_41FEB0], eax
mov [eax+0x4], edx
mov [eax+0x10], ecx
mov byte [eax+0x19], 0x1
mov [eax+0xc], ecx
mov byte [eax+0x1a], 0xff
mov ecx, [loc_41FF18]
dec ecx
cmp edi, ecx
mov [loc_41FF18], ecx
jl short loc_40214D
loc_4021A4:
mov [loc_41FF14], ecx
pop edi
pop ecx
ret
align 16
loc_4021B0:
push ecx
mov edx, [loc_41FF14]
mov eax, ecx
mov ecx, [loc_41FF18]
push ebp
cmp ecx, edx
jle short loc_402235
xor edx, edx
mov cl, 0x1
jmp short loc_4021CE
loc_4021CA:
mov eax, [esp+0x4]
loc_4021CE:
mov ebp, eax
dec eax
test ebp, ebp
mov [esp+0x4], eax
jz short loc_402235
mov eax, [loc_41FEB8]
cmp eax, loc_41FEB8
jz short loc_402235
mov ebp, [eax]
mov dword [ebp+0x4], loc_41FEB8
mov ebp, [eax]
mov [loc_41FEB8], ebp
mov ebp, [loc_41FEB0]
mov [eax], ebp
mov ebp, [loc_41FEB0]
mov [ebp+0x4], eax
mov [loc_41FEB0], eax
mov dword [eax+0x4], loc_41FEB0
mov [eax+0x10], edx
mov [eax+0x19], cl
mov [eax+0xc], edx
mov byte [eax+0x1a], 0xff
mov eax, [loc_41FF18]
mov ebp, [loc_41FF14]
dec eax
cmp eax, ebp
mov [loc_41FF18], eax
jg short loc_4021CA
loc_402235:
pop ebp
pop ecx
ret
align 16
loc_402240:
push ecx
mov eax, [loc_41FF18]
push ebx
mov edx, 0x7c
push ebp
push esi
cmp eax, edx
push edi
mov [esp+0x10], ecx
jge near loc_402402
loc_40225B:
mov eax, [loc_41FEB4]
cmp eax, loc_41FEB0
jz short loc_4022C7
mov esi, [eax+0x4]
lea ecx, [eax+0x4]
mov [loc_41FEB4], esi
xor edi, edi
mov esi, [ecx]
cmp eax, edi
mov dword [esi], loc_41FEB0
jz short loc_4022C0
mov esi, [loc_41FEB8]
mov [eax], esi
mov esi, [loc_41FEB8]
mov [esi+0x4], eax
mov [loc_41FEB8], eax
mov dword [ecx], loc_41FEB8
mov [eax+0x10], edi
mov byte [eax+0x19], 0x1
mov [eax+0xc], edi
mov byte [eax+0x1a], 0xff
mov eax, [loc_41FF18]
inc eax
cmp eax, edx
mov [loc_41FF18], eax
jge near loc_402402
jmp short loc_40225B
loc_4022C0:
mov eax, [loc_41FEB4]
jmp short loc_4022C9
loc_4022C7:
xor edi, edi
loc_4022C9:
cmp [loc_41FF18], edx
jge near loc_402402
jmp short loc_4022DC
loc_4022D7:
mov eax, [loc_41FEB4]
loc_4022DC:
cmp [esp+0x10], edi
jz near loc_402402
cmp eax, loc_41FEB0
jz short loc_402309
mov edx, [eax+0x4]
lea ecx, [eax+0x4]
mov [loc_41FEB4], edx
cmp eax, edi
mov ecx, [ecx]
mov dword [ecx], loc_41FEB0
jnz near loc_4023BA
loc_402309:
xor esi, esi
mov ecx, loc_42A95F
mov ebp, loc_41FED0
mov ebx, 0x10
loc_40231A:
mov al, [ecx]
mov dl, [ecx+0x1]
cmp al, dl
jbe short loc_402335
sub al, dl
lea edx, [ecx-0x57]
mov [esi+loc_41FEC0], al
mov [ebp], edx
inc esi
add ebp, 0x4
loc_402335:
add ecx, 0x104
dec ebx
jnz short loc_40231A
mov byte [esi+loc_41FEC0], 0x0
mov dl, [loc_41FEC0]
xor ebx, ebx
mov [esi*4+loc_41FED0], edi
test dl, dl
jz short loc_4023AB
mov esi, loc_41FED0
loc_40235D:
mov al, [ebx+loc_41FEC1]
mov ebp, [esi]
lea ecx, [ebx+loc_41FEC1]
test al, al
jz short loc_40239D
mov edi, ecx
lea ecx, [esi+0x4]
loc_402374:
cmp al, dl
ja short loc_40237E
jb short loc_402390
cmp [ecx], ebp
jbe short loc_402390
loc_40237E:
mov [ebx+loc_41FEC0], al
mov [edi], dl
mov dl, al
mov eax, [ecx]
mov [esi], eax
mov [ecx], ebp
mov ebp, [esi]
loc_402390:
mov al, [edi+0x1]
add ecx, 0x4
inc edi
test al, al
jnz short loc_402374
xor edi, edi
loc_40239D:
mov dl, [ebx+loc_41FEC1]
inc ebx
add esi, 0x4
test dl, dl
jnz short loc_40235D
loc_4023AB:
mov [loc_41FF10], ebx
call loc_401AD0
cmp eax, edi
jz short loc_402402
loc_4023BA:
mov ecx, [loc_41FEB8]
mov [eax], ecx
mov edx, [loc_41FEB8]
mov [edx+0x4], eax
mov edx, [esp+0x10]
mov [loc_41FEB8], eax
mov dword [eax+0x4], loc_41FEB8
mov [eax+0x10], edi
mov byte [eax+0x19], 0x1
mov [eax+0xc], edi
mov byte [eax+0x1a], 0xff
mov eax, [loc_41FF18]
inc eax
dec edx
cmp eax, 0x7c
mov [loc_41FF18], eax
mov [esp+0x10], edx
jl near loc_4022D7
loc_402402:
pop edi
pop esi
pop ebp
pop ebx
pop ecx
ret
align 16
loc_402410:
push ecx
mov eax, [loc_41FF18]
cmp eax, 0x7c
jl short loc_402434
xor edx, edx
mov ecx, 0x1
call loc_40A480
xor edx, edx
xor ecx, ecx
call loc_40A480
pop ecx
ret 0x4
loc_402434:
mov ecx, 0x80
sub ecx, eax
mov [esp], ecx
fild dword [esp]
fmul dword [esp+0x8]
call _ftol_asm
mov ecx, eax
call loc_402240
pop ecx
ret 0x4
loc_404760:
mov al, [esp+0x4]
test al, al
jnz short loc_40478A
cmp byte [ecx+0x1], 0x9
jnz short loc_40478A
mov al, [ecx+0x2]
test al, al
jbe short loc_40478A
cmp al, 0x2
ja short loc_40478A
cmp edx, 0x4
jnz short loc_40478A
cmp byte [ecx], 0x7f
jnz short loc_40478A
xor ecx, ecx
call loc_4065F0
loc_40478A:
ret 0x4
align 16
loc_404790:
mov al, [esp+0x4]
test al, al
jnz short loc_4047E1
cmp byte [ecx], 0x7f
jnz short loc_4047E1
cmp byte [ecx+0x1], 0x4
jnz short loc_4047E1
xor eax, eax
mov al, [ecx+0x2]
dec eax
jnz short loc_4047E1
cmp edx, 0x6
jnz short loc_4047E1
xor eax, eax
mov al, [ecx+0x4]
mov [esp+0x4], eax
fild dword [esp+0x4]
fmul dword [loc_4181E0]
fld st0
fmul st0, st1
fstp dword [loc_41B6B8]
fstp st0
fld dword [loc_41B6BC]
fmul dword [loc_41B6B8]
fstp dword [loc_41B6FC]
loc_4047E1:
ret 0x4
align 16
loc_4047F0:
mov al, [esp+0x4]
test al, al
jnz short loc_404833
mov al, [ecx]
and al, 0xf0
cmp al, 0x10
jnz short loc_404833
cmp byte [ecx+0x1], 0x4c
jnz short loc_404833
cmp edx, 0x7
jl short loc_404833
xor edx, edx
xor eax, eax
mov dl, [ecx+0x2]
mov al, [ecx+0x3]
shl edx, 0x7
or edx, eax
xor eax, eax
mov al, [ecx+0x4]
shl edx, 0x7
or edx, eax
cmp edx, 0x7e
jnz short loc_404833
mov ecx, 0x1
call loc_4065F0
loc_404833:
ret 0x4
align 16
loc_404840:
push ebx
mov ebx, ecx
push ebp
push esi
mov al, [ebx+0x1]
push edi
cmp al, 0x42
mov ebp, edx
jnz near loc_40496E
cmp byte [ebx+0x2], 0x12
jnz near loc_40496E
cmp ebp, 0x9
jl near loc_40496E
xor ecx, ecx
xor eax, eax
mov cl, [ebx+0x3]
mov al, [ebx+0x4]
shl ecx, 0x7
or ecx, eax
xor edx, edx
mov dl, [ebx+0x5]
add ebx, 0x6
shl ecx, 0x7
or ecx, edx
cmp ecx, 0x7f
jz near loc_40495C
cmp ecx, 0x10007f
jz near loc_404941
mov eax, ecx
sub ebp, 0x8
and eax, 0x1ff800
cmp eax, 0x100800
jnz short loc_4048F3
mov edx, ecx
and edx, 0x7f
cmp dl, 0x15
jnz near loc_40496E
mov al, [esp+0x14]
pop edi
shr ecx, 0x7
and cl, 0xf
pop esi
shl al, 0x4
add cl, al
pop ebp
mov [esp+0x8], cl
mov ecx, [esp+0x8]
and ecx, 0xff
mov eax, ecx
shl eax, 0x6
add eax, ecx
mov cl, [ebx]
shl eax, 0x2
pop ebx
mov [eax+loc_42A966], cl
mov byte [eax+loc_42A965], 0x0
ret 0x4
loc_4048F3:
mov al, [esp+0x14]
test al, al
jnz short loc_40496E
mov eax, [(loc_41B1E8 + (8))]
test eax, eax
jz short loc_40496E
mov edi, (loc_41B1E8 + (4))
loc_404909:
mov eax, [edi-0x4]
cmp ecx, eax
jb short loc_404930
mov esi, [edi]
cmp ecx, esi
jae short loc_404930
sub esi, ecx
cmp esi, ebp
jle short loc_40491E
mov esi, ebp
loc_40491E:
push ebx
mov edx, esi
sub ecx, eax
call dword [edi+0x4]
sub ebp, esi
test ebp, ebp
jle short loc_40496E
mov ecx, [edi]
add ebx, esi
loc_404930:
mov eax, [edi+0x10]
add edi, 0xc
test eax, eax
jnz short loc_404909
pop edi
pop esi
pop ebp
pop ebx
ret 0x4
loc_404941:
cmp byte [ebx], 0x0
jz short loc_40495C
mov al, [esp+0x14]
test al, al
jnz short loc_40496E
xor ecx, ecx
call loc_4065F0
pop edi
pop esi
pop ebp
pop ebx
ret 0x4
loc_40495C:
mov al, [esp+0x14]
test al, al
jnz short loc_40496E
mov ecx, 0x2
call loc_4065F0
loc_40496E:
pop edi
pop esi
pop ebp
pop ebx
ret 0x4
align 16
loc_404980:
mov eax, edx
dec edx
push esi
mov esi, ecx
test eax, eax
jz short loc_4049C1
push ebx
push edi
mov edi, [esp+0x10]
lea ebx, [edx+0x1]
loc_404993:
cmp esi, 0x4
ja short loc_4049BA
jmp dword [esi*4+loc_4049C8]
loc_40499F:
xor ecx, ecx
mov cl, [edi]
call loc_408840
jmp short loc_4049BA
loc_4049AA:
mov cl, [edi]
call loc_408950
jmp short loc_4049BA
loc_4049B3:
mov cl, [edi]
call loc_408980
loc_4049BA:
inc esi
inc edi
dec ebx
jnz short loc_404993
pop edi
pop ebx
loc_4049C1:
pop esi
ret 0x4
align 4
loc_4049C8:
dd loc_40499F
dd loc_40499F
dd loc_4049BA
dd loc_4049AA
dd loc_4049B3
align 4
align 16
loc_4049E0:
mov eax, edx
dec edx
push edi
mov edi, ecx
test eax, eax
jz short loc_404A56
push ebx
push esi
mov esi, [esp+0x10]
lea ebx, [edx+0x1]
loc_4049F3:
cmp edi, 0x6
ja short loc_404A4F
jmp dword [edi*4+loc_404A5C]
loc_4049FF:
xor ecx, ecx
mov cl, [esi]
call loc_408610
jmp short loc_404A4F
loc_404A0A:
mov al, [esi]
shl al, 1
xor ecx, ecx
mov [loc_455D61], al
mov cl, al
mov [esp+0x10], ecx
fild dword [esp+0x10]
fmul dword [loc_4181E0]
fstp dword [loc_44587C]
jmp short loc_404A4F
loc_404A2D:
mov cl, [esi]
call loc_4086A0
jmp short loc_404A4F
loc_404A36:
mov cl, [esi]
call loc_4086E0
jmp short loc_404A4F
loc_404A3F:
mov cl, [esi]
call loc_408720
jmp short loc_404A4F
loc_404A48:
mov cl, [esi]
call loc_408760
loc_404A4F:
inc edi
inc esi
dec ebx
jnz short loc_4049F3
pop esi
pop ebx
loc_404A56:
pop edi
ret 0x4
align 4
loc_404A5C:
dd loc_4049FF
dd loc_404A4F
dd loc_404A0A
dd loc_404A2D
dd loc_404A36
dd loc_404A3F
dd loc_404A48
align 4
align 16
loc_404A80:
mov ecx, [esp+0x4]
xor eax, eax
mov al, [ecx]
mov [esp+0x4], eax
fild dword [esp+0x4]
fmul dword [loc_4181E0]
fld st0
fmul st0, st1
fstp dword [loc_41B6B8]
fstp st0
fld dword [loc_41B6BC]
fmul dword [loc_41B6B8]
fstp dword [loc_41B6FC]
ret 0x4
loc_4056C0:
sub esp, 0x10
mov [loc_42A2E0], ecx
mov eax, [ecx+0x28]
push ebx
push ebp
lea ebx, [ecx+edx]
cmp eax, ebx
jne short loc_4056CE_1
sub eax, ecx
loc_4056CE_1:
xor bl, bl ; check if the datafile was already initialized (in another instance)
push esi
cmp edx, eax
push edi
jnz near loc_4058D9
cmp dword [ecx+0x20], 0x200
jnz near loc_4058D9
mov edx, [ecx+0x24]
cmp edx, 0x100
jz short loc_4056FE
cmp edx, 0x101
jnz near loc_4058D9
loc_4056FE:
mov esi, [ecx+0x34]
mov ebp, [ecx+0x2c]
mov edi, [ecx+0x30]
cmp eax, [ecx+0x28]
jne loc_4058CC ; check if the datafile was already initialized (in another instance)
add esi, ecx
add eax, ecx
add ebp, ecx
mov edx, esi
mov [ecx+0x28], eax
mov eax, ebp
mov [esp+0x1c], edx
mov edx, [ecx+0x38]
mov [esp+0x14], eax
mov eax, [ecx+0x3c]
add edx, ecx
add edi, ecx
mov [ecx+0x38], edx
add eax, ecx
xor edx, edx
mov [ecx+0x2c], ebp
mov [ecx+0x30], edi
mov [ecx+0x34], esi
mov [ecx+0x3c], eax
mov ebp, [loc_42A2E0]
mov [esp+0x10], edx
loc_405743:
xor esi, esi
shl edx, 0x7
lea eax, [edx+ebp+0x50]
mov [esp+0x18], eax
loc_405750:
mov eax, [esp+0x18]
xor edx, edx
mov dl, [eax+esi]
mov eax, [esp+0x14]
shl edx, 0x8
add edx, eax
cmp edx, edi
ja near loc_4058D9
mov edx, [esp+0x10]
mov eax, edx
sub eax, 0x0
jz short loc_40578B
dec eax
jnz near loc_4058D9
cmp bl, [esi+ebp+0xd0]
jae near loc_4058D9
jmp short loc_405795
loc_40578B:
mov al, [esi+ebp+0x50]
cmp bl, al
jae short loc_405795
mov bl, al
loc_405795:
inc esi
cmp esi, 0x80
jl short loc_405750
inc edx
cmp edx, 0x2
mov [esp+0x10], edx
jl short loc_405743
mov edx, [esp+0x14]
inc bl
mov [esp+0x18], bl
mov ebx, [esp+0x1c]
xor esi, esi
cmp edx, edi
mov ebp, edi
mov [esp+0x10], ebx
jae short loc_4057DA
mov eax, [esp+0x18]
sub edi, edx
add edi, 0xff
and eax, 0xff
shr edi, 0x8
loc_4057D6:
inc esi
dec edi
jnz short loc_4057D6
loc_4057DA:
cmp ebx, ebp
jbe short loc_40581A
loc_4057DE:
xor ebx, ebx
lea esi, [ebp+0x14]
loc_4057E3:
mov eax, [esi]
mov edi, [ecx+0x38]
cmp eax, 0xffffffff
lea edx, [eax+edi]
jnz short loc_4057F4
xor edx, edx
jmp short loc_405805
loc_4057F4:
cmp edx, edi
jb near loc_4058D9
cmp edx, [ecx+0x3c]
jae near loc_4058D9
loc_405805:
mov [esi], edx
inc ebx
add esi, 0x4
cmp ebx, 0x10
jl short loc_4057E3
mov eax, [ecx+0x34]
add ebp, 0x54
cmp eax, ebp
ja short loc_4057DE
loc_40581A:
mov edx, [esp+0x10]
mov eax, [ecx+0x38]
cmp eax, edx
jbe short loc_405875
loc_405825:
mov eax, [esp+0x10]
xor ebx, ebx
lea esi, [eax+0x84]
loc_405831:
mov eax, [esi]
mov edi, [ecx+0x38]
cmp eax, 0xffffffff
lea edx, [eax+edi]
jnz short loc_405842
xor edx, edx
jmp short loc_405853
loc_405842:
cmp edx, edi
jb near loc_4058D9
cmp edx, [ecx+0x3c]
jae near loc_4058D9
loc_405853:
mov [esi], edx
inc ebx
add esi, 0x4
cmp ebx, 0x80
jl short loc_405831
mov eax, [esp+0x10]
mov edx, [ecx+0x38]
add eax, 0x284
cmp edx, eax
mov [esp+0x10], eax
ja short loc_405825
loc_405875:
mov ebp, [ecx+0x38]
mov eax, [ecx+0x3c]
cmp eax, ebp
jbe short loc_4058CC
loc_40587F:
xor ebx, ebx
lea edi, [ebp+0x4]
loc_405884:
mov edx, [edi]
mov esi, [ecx+0x3c]
cmp edx, 0xffffffff
lea eax, [edx+esi]
jnz short loc_405895
xor eax, eax
jmp short loc_4058B7
loc_405895:
cmp eax, esi
jb short loc_4058D9
cmp eax, [ecx+0x28]
jae short loc_4058D9
mov dx, [eax]
test dx, dx
lea esi, [edx+0x1]
mov [eax], si
jnz short loc_4058B7
mov edx, [ecx+0x3c]
mov esi, [eax+0x4]
add esi, edx
mov [eax+0x4], esi
loc_4058B7:
mov [edi], eax
inc ebx
add edi, 0xc
cmp ebx, 0x2
jl short loc_405884
mov eax, [ecx+0x3c]
add ebp, 0x50
cmp eax, ebp
ja short loc_40587F
loc_4058CC:
pop edi
pop esi
pop ebp
mov eax, 0x1
pop ebx
add esp, 0x10
ret
loc_4058D9:
pop edi
pop esi
pop ebp
xor eax, eax
pop ebx
add esp, 0x10
ret
loc_405910:
push ebx
mov bl, [esp+0x8]
push esi
xor eax, eax
mov esi, ecx
push edi
mov ecx, [loc_42A2E0]
test bl, bl
setnz al
shl eax, 0x7
mov edi, ecx
and esi, 0xff
add edi, eax
xor eax, eax
and edx, 0xff
mov al, [esi+edi+0x50]
shl eax, 0x7
add eax, edx
mov edx, [ecx+0x2c]
mov ax, [edx+eax*2]
cmp ax, 0xffff
jnz short loc_405959
pop edi
pop esi
xor eax, eax
pop ebx
ret 0x4
loc_405959:
test bl, bl
jz short loc_405976
and eax, 0xffff
pop edi
pop esi
pop ebx
lea edx, [eax+eax*4]
shl edx, 0x5
add edx, eax
mov eax, [ecx+0x34]
lea eax, [eax+edx*4]
ret 0x4
loc_405976:
mov ecx, [ecx+0x30]
and eax, 0xffff
pop edi
pop esi
lea edx, [eax+eax*4]
pop ebx
lea eax, [eax+edx*4]
lea eax, [ecx+eax*4]
ret 0x4
align 16
loc_405990:
sub esp, 0x8
push ebx
push ebp
push esi
push edi
xor ebx, ebx
mov ecx, 0x20
xor eax, eax
mov edi, loc_42A2FC
mov [loc_42A2F8], ebx
mov esi, loc_42A37C
rep stosd
mov ecx, 0x20
or eax, 0xffffffff
mov edi, loc_42A37C
rep stosd
mov ecx, 0x20
mov edi, loc_42A3FC
rep movsd
mov ecx, 0x20
mov esi, loc_42A37C
mov edi, loc_42A47C
rep movsd
mov ecx, 0x81
mov esi, loc_42A2F8
mov edi, loc_42A4FC
rep movsd
mov ecx, 0x81
mov esi, loc_42A2F8
mov edi, loc_42A700
rep movsd
mov ecx, 0x4
call loc_408840
mov ecx, 0x2
call loc_408610
xor edx, edx
mov [loc_42BA08], ebx
mov [esp+0x10], edx
mov ebp, loc_42A910
loc_405A25:
mov ecx, 0x20
xor eax, eax
lea edi, [ebp+0x79]
mov esi, [loc_42A2F4]
rep stosd
lea eax, [ebp-0x8]
mov cl, [edx+loc_41B6A8]
mov [ebp-0x4], eax
mov [ebp+0x52], cl
mov [eax], eax
lea eax, [ebp+0x8]
mov [ebp+0x4], ebp
mov [ebp], ebp
mov [ebp+0xc], eax
mov [eax], eax
mov al, [edx+loc_41B698]
mov ecx, [loc_42A2EC]
mov [ebp+0x50], al
mov eax, 0x43ec3871
lea edx, [ebp+0x59]
mov [ebp+0x34], eax
mov [ebp+0x38], eax
mov eax, [loc_42A2E8]
mov edi, edx
mov edx, [loc_42A2F0]
cmp ebp, loc_42A910
mov [ebp+0x10], ebx
mov [edi], eax
mov [ebp+0x14], ebx
mov [ebp+0x51], bl
mov [ebp+0x4f], bl
mov [edi+0x4], ecx
mov dword [ebp+0x1c], 0x44fa0000
mov [ebp+0x20], ebx
mov [ebp+0x24], ebx
mov [edi+0x8], edx
mov [ebp+0x28], ebx
mov dword [ebp+0x2c], 0x3f800000
mov dword [ebp+0x30], 0x3f1eb867
mov [edi+0xc], esi
lea edi, [ebp+0x69]
mov [ebp+0x4c], bl
mov [ebp+0x40], ebx
mov [edi], eax
mov [ebp+0x3c], ebx
mov [ebp+0x54], bl
mov [ebp+0x53], bl
mov [edi+0x4], ecx
mov [ebp+0x48], ebx
mov [ebp+0x4e], bl
mov [ebp+0x4d], bl
mov [edi+0x8], edx
mov [ebp+0x55], bl
mov [ebp+0x58], bl
mov [ebp+0x57], bl
mov [edi+0xc], esi
jz short loc_405B01
cmp ebp, loc_42B950
jz short loc_405B01
mov esi, loc_42A2F8
mov [ebp+0x56], bl
mov [ebp+0x18], esi
jmp short loc_405B11
loc_405B01:
mov dword [ebp+0x18], loc_42A4FC
mov byte [ebp+0x56], 0x1
mov esi, loc_42A2F8
loc_405B11:
mov al, [ebp+0x56]
xor dl, dl
push eax
xor cl, cl
call loc_405910
mov cl, [ebp+0x56]
cmp cl, bl
jz short loc_405B6E
jbe short loc_405B69
cmp cl, 0x2
ja short loc_405B69
mov [esp+0x14], cl
mov [ebp+0x14], eax
mov eax, [esp+0x14]
mov [ebp+0x10], ebx
and eax, 0xff
mov ecx, eax
shl ecx, 0x7
add ecx, eax
mov eax, [ecx*4+loc_42A2F8]
cmp eax, ebx
lea edi, [ecx*4+loc_42A2F8]
mov [ebp+0x18], edi
jz short loc_405B77
mov ecx, 0x81
mov esi, loc_42A2F8
rep movsd
jmp short loc_405B77
loc_405B69:
mov [ebp+0x10], ebx
jmp short loc_405B71
loc_405B6E:
mov [ebp+0x10], eax
loc_405B71:
mov [ebp+0x14], ebx
mov [ebp+0x18], esi
loc_405B77:
mov edx, [esp+0x10]
mov dword [ebp+0x44], 0x3da14285
add ebp, 0x104
inc edx
cmp ebp, loc_42B950
mov [esp+0x10], edx
jl near loc_405A25
mov dword [loc_41B6B8], 0x3f4ccccd
mov dword [loc_41B6BC], 0x3f800000
mov dword [loc_41B6FC], 0x3f4ccccd
xor ecx, ecx
mov esi, 0x7f7f
loc_405BBE:
cmp ecx, 0x9
jge short loc_405BD3
mov edx, ecx
shl edx, 0x6
add edx, ecx
lea edx, [edx*4+loc_42AA0C]
jmp short loc_405BEA
loc_405BD3:
jnz short loc_405BDC
mov edx, loc_42A908
jmp short loc_405BEA
loc_405BDC:
mov eax, ecx
shl eax, 0x6
add eax, ecx
lea edx, [eax*4+loc_42A908]
loc_405BEA:
lea eax, [ecx+ecx*2]
shl eax, 0x2
inc ecx
mov [eax+loc_42B948], edx
mov [eax+loc_42B94E], si
mov [eax+loc_42B94C], si
cmp ecx, 0x10
mov [eax+loc_42B950], bx
jl short loc_405BBE
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x8
ret
loc_405C80:
push esi
push edi
mov edi, [ecx+0x18]
test edi, edi
jz short loc_405CA7
lea esi, [edi+0x3]
xor eax, eax
loc_405C8E:
mov cl, [esi]
inc esi
cmp cl, dl
jae short loc_405CA0
inc eax
cmp eax, 0x10
jl short loc_405C8E
loc_405C9B:
pop edi
xor eax, eax
pop esi
ret
loc_405CA0:
mov eax, [edi+eax*4+0x14]
pop edi
pop esi
ret
loc_405CA7:
mov ecx, [ecx+0x1c]
test ecx, ecx
jz short loc_405C9B
and edx, 0xff
pop edi
pop esi
mov eax, [ecx+edx*4+0x84]
ret
align 16
loc_405CC0:
push ebx
mov bl, [esp+0x8]
push ebp
push esi
push edi
xor esi, esi
lea eax, [ecx+0x4]
mov edi, edx
mov ebp, 0x2
loc_405CD4:
cmp [eax+0x8], bl
ja short loc_405CF0
cmp [eax+0xa], bl
jb short loc_405CF0
mov ecx, [eax]
test ecx, ecx
jz short loc_405CF0
cmp dword [ecx+0x4], 0x0
jz short loc_405CF0
mov [edi], eax
inc esi
add edi, 0x4
loc_405CF0:
add eax, 0xc
dec ebp
jnz short loc_405CD4
cmp esi, 0x2
jge short loc_405D09
mov ecx, 0x2
lea edi, [edx+esi*4]
sub ecx, esi
xor eax, eax
rep stosd
loc_405D09:
pop edi
pop esi
pop ebp
pop ebx
ret 0x4
loc_405D10:
mov eax, [esp+0x4]
and edx, 0xff
and eax, 0xff
push esi
shl eax, 0x7
or eax, edx
sub eax, 0x2000
mov [esp+0x8], eax
fild dword [esp+0x8]
fmul dword [loc_4181E4]
fcom dword [ecx+0x28]
fnstsw ax
test ah, 0x40
jnz near loc_405DCA
mov eax, [ecx]
fstp dword [ecx+0x28]
cmp eax, ecx
jz short loc_405D70
loc_405D4F:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov edx, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fstp dword [edx+0x40]
mov eax, [eax]
cmp eax, ecx
jnz short loc_405D4F
loc_405D70:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_405D9B
loc_405D7A:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_405D7A
loc_405D9B:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_405DCC
loc_405DA5:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_405DA5
pop esi
ret 0x4
loc_405DCA:
fstp st0
loc_405DCC:
pop esi
ret 0x4
loc_405DD0:
push ebx
push ebp
push esi
mov esi, ecx
mov eax, 0x3f1eb867
push edi
cmp [esi+0x38], eax
jz short loc_405E45
mov [esi+0x38], eax
mov eax, [esi]
cmp eax, esi
jz short loc_405E01
loc_405DE9:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov ecx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [ecx+0x90]
mov eax, [eax]
cmp eax, esi
jnz short loc_405DE9
loc_405E01:
mov eax, [esi+0x8]
lea ecx, [esi+0x8]
cmp eax, ecx
jz short loc_405E23
loc_405E0B:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov edx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_405E0B
loc_405E23:
mov eax, [esi+0x10]
lea ecx, [esi+0x10]
cmp eax, ecx
jz short loc_405E45
loc_405E2D:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov edx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_405E2D
loc_405E45:
mov al, [esi+0x54]
xor ebx, ebx
cmp al, bl
jz short loc_405EAD
mov edi, [esi]
mov [esi+0x54], bl
cmp edi, esi
jz short loc_405E6D
loc_405E57:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, esi
jnz short loc_405E57
loc_405E6D:
mov edi, [esi+0x8]
lea ebp, [esi+0x8]
cmp edi, ebp
jz short loc_405E8D
loc_405E77:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, ebp
jnz short loc_405E77
loc_405E8D:
mov edi, [esi+0x10]
lea ebp, [esi+0x10]
cmp edi, ebp
jz short loc_405EAD
loc_405E97:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, ebp
jnz short loc_405E97
loc_405EAD:
mov ecx, [esi+0x34]
mov eax, 0x3f800000
cmp ecx, eax
jz short loc_405F1E
mov [esi+0x34], eax
mov eax, [esi]
cmp eax, esi
jz short loc_405EDA
loc_405EC2:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov ecx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [ecx+0x90]
mov eax, [eax]
cmp eax, esi
jnz short loc_405EC2
loc_405EDA:
mov eax, [esi+0x8]
lea ecx, [esi+0x8]
cmp eax, ecx
jz short loc_405EFC
loc_405EE4:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov edx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_405EE4
loc_405EFC:
mov eax, [esi+0x10]
lea ecx, [esi+0x10]
cmp eax, ecx
jz short loc_405F1E
loc_405F06:
fld dword [eax+0x20]
fmul dword [esi+0x38]
mov edx, [eax+0x10]
fmul dword [esi+0x34]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_405F06
loc_405F1E:
xor dl, dl
mov ecx, esi
call loc_401590
cmp [esi+0x5b], bl
jz short loc_405F3E
mov edx, loc_4065C0
mov ecx, esi
mov [esi+0x5b], bl
mov [esi+0x44], ebx
call loc_405FD0
loc_405F3E:
fld dword [esi+0x28]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x40
jnz short loc_405FAA
mov eax, [esi]
mov [esi+0x28], ebx
cmp eax, esi
jz short loc_405F78
loc_405F57:
fld dword [esi+0x24]
fmul dword [esi+0x28]
mov ecx, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [esi+0x30]
fadd dword [esi+0x2c]
fstp dword [ecx+0x40]
mov eax, [eax]
cmp eax, esi
jnz short loc_405F57
loc_405F78:
mov edi, [esi+0x8]
lea ebx, [esi+0x8]
cmp edi, ebx
jz short loc_405F91
loc_405F82:
mov edx, edi
mov ecx, esi
call loc_405FB0
mov edi, [edi]
cmp edi, ebx
jnz short loc_405F82
loc_405F91:
mov edi, [esi+0x10]
lea ebx, [esi+0x10]
cmp edi, ebx
jz short loc_405FAA
loc_405F9B:
mov edx, edi
mov ecx, esi
call loc_405FB0
mov edi, [edi]
cmp edi, ebx
jnz short loc_405F9B
loc_405FAA:
pop edi
pop esi
pop ebp
pop ebx
ret
align 16
loc_405FB0:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov eax, [edx+0x10]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fadd dword [edx+0x1c]
fadd dword [loc_42BA08]
fstp dword [eax+0x40]
ret
align 16
loc_405FD0:
push ebx
push ebp
push esi
mov esi, ecx
push edi
mov ebx, edx
mov edi, [esi]
cmp edi, esi
jz short loc_405FEA
loc_405FDE:
mov edx, edi
mov ecx, esi
call ebx
mov edi, [edi]
cmp edi, esi
jnz short loc_405FDE
loc_405FEA:
mov edi, [esi+0x8]
lea ebp, [esi+0x8]
cmp edi, ebp
jz short loc_406000
loc_405FF4:
mov edx, edi
mov ecx, esi
call ebx
mov edi, [edi]
cmp edi, ebp
jnz short loc_405FF4
loc_406000:
mov edi, [esi+0x10]
lea ebp, [esi+0x10]
cmp edi, ebp
jz short loc_406016
loc_40600A:
mov edx, edi
mov ecx, esi
call ebx
mov edi, [edi]
cmp edi, ebp
jnz short loc_40600A
loc_406016:
pop edi
pop esi
pop ebp
pop ebx
ret
align 16
loc_406020:
push ecx
and edx, 0xff
push esi
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4181E0]
fld st0
fmulp st1, st0
fcom dword [ecx+0x38]
fnstsw ax
test ah, 0x40
jnz short loc_4060AC
mov eax, [ecx]
fstp dword [ecx+0x38]
cmp eax, ecx
jz short loc_406065
loc_40604D:
fld dword [eax+0x20]
fmul dword [ecx+0x34]
mov edx, [eax+0x10]
fmul dword [ecx+0x38]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_40604D
loc_406065:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_406087
loc_40606F:
fld dword [eax+0x20]
fmul dword [ecx+0x34]
mov esi, [eax+0x10]
fmul dword [ecx+0x38]
fstp dword [esi+0x90]
mov eax, [eax]
cmp eax, edx
jnz short loc_40606F
loc_406087:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_4060AE
loc_406091:
fld dword [eax+0x20]
fmul dword [ecx+0x34]
mov esi, [eax+0x10]
fmul dword [ecx+0x38]
fstp dword [esi+0x90]
mov eax, [eax]
cmp eax, edx
jnz short loc_406091
pop esi
pop ecx
ret
loc_4060AC:
fstp st0
loc_4060AE:
pop esi
pop ecx
ret
align 16
loc_4060C0:
push ebx
push esi
mov esi, ecx
sub dl, 0x40
push edi
cmp [esi+0x54], dl
jz short loc_40612C
mov edi, [esi]
mov [esi+0x54], dl
cmp edi, esi
jz short loc_4060EC
loc_4060D6:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, esi
jnz short loc_4060D6
loc_4060EC:
mov edi, [esi+0x8]
lea ebx, [esi+0x8]
cmp edi, ebx
jz short loc_40610C
loc_4060F6:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, ebx
jnz short loc_4060F6
loc_40610C:
mov edi, [esi+0x10]
lea ebx, [esi+0x10]
cmp edi, ebx
jz short loc_40612C
loc_406116:
mov ecx, [edi+0x10]
push 0x1
push edi
mov edx, esi
add ecx, 0x7c
call loc_409880
mov edi, [edi]
cmp edi, ebx
jnz short loc_406116
loc_40612C:
pop edi
pop esi
pop ebx
ret
loc_406130:
push ecx
and edx, 0xff
push esi
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4181E0]
fld st0
fmulp st1, st0
fcom dword [ecx+0x34]
fnstsw ax
test ah, 0x40
jnz short loc_4061BC
mov eax, [ecx]
fstp dword [ecx+0x34]
cmp eax, ecx
jz short loc_406175
loc_40615D:
fld dword [eax+0x20]
fmul dword [ecx+0x38]
mov edx, [eax+0x10]
fmul dword [ecx+0x34]
fstp dword [edx+0x90]
mov eax, [eax]
cmp eax, ecx
jnz short loc_40615D
loc_406175:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_406197
loc_40617F:
fld dword [eax+0x20]
fmul dword [ecx+0x38]
mov esi, [eax+0x10]
fmul dword [ecx+0x34]
fstp dword [esi+0x90]
mov eax, [eax]
cmp eax, edx
jnz short loc_40617F
loc_406197:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_4061BE
loc_4061A1:
fld dword [eax+0x20]
fmul dword [ecx+0x38]
mov esi, [eax+0x10]
fmul dword [ecx+0x34]
fstp dword [esi+0x90]
mov eax, [eax]
cmp eax, edx
jnz short loc_4061A1
pop esi
pop ecx
ret
loc_4061BC:
fstp st0
loc_4061BE:
pop esi
pop ecx
ret
align 16
loc_4061D0:
push ecx
mov al, [ecx+0x5b]
push esi
cmp dl, al
jz near loc_4062A4
mov [ecx+0x5b], dl
and edx, 0xff
mov [esp+0x4], edx
mov edx, [ecx]
fild dword [esp+0x4]
cmp edx, ecx
fmul dword [ecx+0x3c]
fmul dword [loc_4181E0]
fstp dword [ecx+0x44]
jz short loc_406230
loc_406200:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_40621B
fld dword [ecx+0x48]
fadd dword [ecx+0x44]
fadd dword [edx+0x24]
jmp short loc_406224
loc_40621B:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_406224:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, ecx
jnz short loc_406200
loc_406230:
mov edx, [ecx+0x8]
lea esi, [ecx+0x8]
cmp edx, esi
jz short loc_40626A
loc_40623A:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_406255
fld dword [ecx+0x48]
fadd dword [ecx+0x44]
fadd dword [edx+0x24]
jmp short loc_40625E
loc_406255:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_40625E:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, esi
jnz short loc_40623A
loc_40626A:
mov edx, [ecx+0x10]
lea esi, [ecx+0x10]
cmp edx, esi
jz short loc_4062A4
loc_406274:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_40628F
fld dword [ecx+0x48]
fadd dword [ecx+0x44]
fadd dword [edx+0x24]
jmp short loc_406298
loc_40628F:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_406298:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, esi
jnz short loc_406274
loc_4062A4:
pop esi
pop ecx
ret
align 16
loc_4062B0:
push ecx
shr dx, 0x7
and edx, 0xffff
push esi
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4181EC]
fcom dword [ecx+0x24]
fnstsw ax
test ah, 0x40
jnz near loc_40635B
mov eax, [ecx]
fstp dword [ecx+0x24]
cmp eax, ecx
jz short loc_406302
loc_4062E1:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov edx, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [edx+0x40]
mov eax, [eax]
cmp eax, ecx
jnz short loc_4062E1
loc_406302:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_40632D
loc_40630C:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_40630C
loc_40632D:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_40635D
loc_406337:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_406337
pop esi
pop ecx
ret
loc_40635B:
fstp st0
loc_40635D:
pop esi
pop ecx
ret
loc_406360:
push ecx
and edx, 0xffff
push esi
shr edx, 0x7
sub edx, 0x40
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4181EC]
fcom dword [ecx+0x2c]
fnstsw ax
test ah, 0x40
jnz near loc_40640D
mov eax, [ecx]
fstp dword [ecx+0x2c]
cmp eax, ecx
jz short loc_4063B4
loc_406393:
fld dword [ecx+0x24]
fmul dword [ecx+0x28]
mov edx, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fstp dword [edx+0x40]
mov eax, [eax]
cmp eax, ecx
jnz short loc_406393
loc_4063B4:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_4063DF
loc_4063BE:
fld dword [ecx+0x24]
fmul dword [ecx+0x28]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_4063BE
loc_4063DF:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_40640F
loc_4063E9:
fld dword [ecx+0x24]
fmul dword [ecx+0x28]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [ecx+0x2c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_4063E9
pop esi
pop ecx
ret
loc_40640D:
fstp st0
loc_40640F:
pop esi
pop ecx
ret
align 16
loc_406420:
push ecx
and edx, 0xffff
push esi
sub edx, 0x2000
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4181F0]
fcom dword [ecx+0x30]
fnstsw ax
test ah, 0x40
jnz near loc_4064CD
mov eax, [ecx]
fstp dword [ecx+0x30]
cmp eax, ecx
jz short loc_406474
loc_406453:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov edx, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [edx+0x40]
mov eax, [eax]
cmp eax, ecx
jnz short loc_406453
loc_406474:
mov eax, [ecx+0x8]
lea edx, [ecx+0x8]
cmp eax, edx
jz short loc_40649F
loc_40647E:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_40647E
loc_40649F:
mov eax, [ecx+0x10]
lea edx, [ecx+0x10]
cmp eax, edx
jz short loc_4064CF
loc_4064A9:
fld dword [ecx+0x28]
fmul dword [ecx+0x24]
mov esi, [eax+0x10]
fadd dword [eax+0x1c]
fadd dword [loc_42BA08]
fadd dword [ecx+0x30]
fadd dword [ecx+0x2c]
fstp dword [esi+0x40]
mov eax, [eax]
cmp eax, edx
jnz short loc_4064A9
pop esi
pop ecx
ret
loc_4064CD:
fstp st0
loc_4064CF:
pop esi
pop ecx
ret
align 16
loc_4064E0:
push ecx
mov al, [ecx+0x5c]
push esi
cmp dl, al
jz near loc_4065B4
mov [ecx+0x5c], dl
and edx, 0xff
mov [esp+0x4], edx
mov edx, [ecx]
fild dword [esp+0x4]
cmp edx, ecx
fmul dword [ecx+0x40]
fmul dword [loc_4181E0]
fstp dword [ecx+0x48]
jz short loc_406540
loc_406510:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_40652B
fld dword [ecx+0x44]
fadd dword [ecx+0x48]
fadd dword [edx+0x24]
jmp short loc_406534
loc_40652B:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_406534:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, ecx
jnz short loc_406510
loc_406540:
mov edx, [ecx+0x8]
lea esi, [ecx+0x8]
cmp edx, esi
jz short loc_40657A
loc_40654A:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_406565
fld dword [ecx+0x44]
fadd dword [ecx+0x48]
fadd dword [edx+0x24]
jmp short loc_40656E
loc_406565:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_40656E:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, esi
jnz short loc_40654A
loc_40657A:
mov edx, [ecx+0x10]
lea esi, [ecx+0x10]
cmp edx, esi
jz short loc_4065B4
loc_406584:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_40659F
fld dword [ecx+0x44]
fadd dword [ecx+0x48]
fadd dword [edx+0x24]
jmp short loc_4065A8
loc_40659F:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
loc_4065A8:
mov eax, [edx+0x10]
fstp dword [eax+0x44]
mov edx, [edx]
cmp edx, esi
jnz short loc_406584
loc_4065B4:
pop esi
pop ecx
ret
align 16
loc_4065C0:
fld dword [edx+0x24]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jnz short loc_4065E0
fld dword [ecx+0x48]
fadd dword [ecx+0x44]
mov eax, [edx+0x10]
fadd dword [edx+0x24]
fstp dword [eax+0x44]
ret
loc_4065E0:
fld dword [edx+0x24]
fsub dword [ecx+0x44]
fsub dword [ecx+0x48]
mov ecx, [edx+0x10]
fstp dword [ecx+0x44]
ret
loc_4065F0:
push ecx
mov eax, ecx
push ebx
mov ecx, [loc_42A4FC]
xor ebx, ebx
push ebp
push esi
cmp ecx, ebx
push edi
jz short loc_406614
mov ecx, 0x81
mov esi, loc_42A2F8
mov edi, loc_42A4FC
rep movsd
loc_406614:
cmp [loc_42A700], ebx
jz short loc_40662D
mov ecx, 0x81
mov esi, loc_42A2F8
mov edi, loc_42A700
rep movsd
loc_40662D:
mov ecx, eax
call loc_40A680
mov ecx, 0x4
call loc_408840
mov ecx, 0x2
call loc_408610
mov dword [loc_42BA08], 0x0
mov ebp, loc_42A95F
loc_406657:
lea ecx, [ebp-0x57]
call loc_401680
mov eax, 0x43ec3871
mov ecx, [loc_42A2EC]
mov [ebp-0x1b], eax
mov [ebp-0x17], eax
lea eax, [ebp+0xa]
mov edx, [loc_42A2F0]
mov edi, eax
mov eax, [loc_42A2E8]
mov esi, [loc_42A2F4]
cmp ebp, loc_42A95F
mov [edi], eax
mov [ebp+0x2], bl
mov [ebp], bl
mov dword [ebp-0x33], 0x44fa0000
mov [edi+0x4], ecx
mov [ebp-0x2f], ebx
mov [ebp-0x2b], ebx
mov [ebp-0x27], ebx
mov [edi+0x8], edx
mov dword [ebp-0x23], 0x3f800000
mov dword [ebp-0x1f], 0x3f1eb867
mov [ebp-0x3], bl
mov [edi+0xc], esi
lea edi, [ebp+0x1a]
mov [ebp-0xf], ebx
mov [ebp-0x13], ebx
mov [edi], eax
mov [ebp+0x5], bl
mov [ebp+0x4], bl
mov [ebp-0x7], ebx
mov [edi+0x4], ecx
mov [ebp-0x1], bl
mov [ebp-0x2], bl
mov [ebp+0x6], bl
mov [edi+0x8], edx
mov [ebp+0x9], bl
mov [ebp+0x8], bl
mov [edi+0xc], esi
jz short loc_406701
cmp ebp, loc_42B99F
jz short loc_406701
mov esi, loc_42A2F8
mov [ebp+0x7], bl
mov [ebp-0x37], esi
jmp short loc_406711
loc_406701:
mov dword [ebp-0x37], loc_42A4FC
mov byte [ebp+0x7], 0x1
mov esi, loc_42A2F8
loc_406711:
mov cl, [ebp+0x7]
xor dl, dl
push ecx
xor cl, cl
call loc_405910
mov cl, [ebp+0x7]
cmp cl, bl
jz short loc_40676E
jbe short loc_406769
cmp cl, 0x2
ja short loc_406769
mov [esp+0x10], cl
mov [ebp-0x3b], eax
mov eax, [esp+0x10]
mov [ebp-0x3f], ebx
and eax, 0xff
mov edx, eax
shl edx, 0x7
add edx, eax
mov eax, [edx*4+loc_42A2F8]
cmp eax, ebx
lea edi, [edx*4+loc_42A2F8]
mov [ebp-0x37], edi
jz short loc_406777
mov ecx, 0x81
mov esi, loc_42A2F8
rep movsd
jmp short loc_406777
loc_406769:
mov [ebp-0x3f], ebx
jmp short loc_406771
loc_40676E:
mov [ebp-0x3f], eax
loc_406771:
mov [ebp-0x3b], ebx
mov [ebp-0x37], esi
loc_406777:
mov dword [ebp-0xb], 0x3da14285
add ebp, 0x104
cmp ebp, loc_42B99F
jl near loc_406657
fld dword [loc_41B6BC]
fmul dword [loc_4181F4]
pop edi
pop esi
pop ebp
mov dword [loc_41B6B8], 0x3f4ccccd
pop ebx
fstp dword [loc_41B6FC]
pop ecx
ret
align 16
loc_4067C0:
mov eax, [ecx+0x1c]
test eax, eax
jz short loc_4067EA
mov eax, [esp+0x4]
push esi
mov esi, [ecx+0x20]
shr eax, 0x7
and al, 0x7f
sub al, 0x40
and edx, 0xff
mov [edx+esi+0x4], al
mov ecx, [ecx+0x20]
pop esi
mov dword [ecx], 0x1
loc_4067EA:
ret 0x4
align 16
loc_4067F0:
mov eax, [ecx+0x1c]
test eax, eax
jz short loc_40681B
mov eax, [esp+0x4]
push esi
mov esi, [ecx+0x20]
shr eax, 0x7
and al, 0x7f
and edx, 0xff
mov [edx+esi+0x84], al
mov ecx, [ecx+0x20]
pop esi
mov dword [ecx], 0x1
loc_40681B:
ret 0x4
align 16
loc_406820:
mov eax, [ecx+0x1c]
test eax, eax
jz short loc_40684D
mov eax, [esp+0x4]
push esi
mov esi, [ecx+0x20]
shr eax, 0x7
and al, 0x7f
sub al, 0x40
and edx, 0xff
mov [edx+esi+0x104], al
mov ecx, [ecx+0x20]
pop esi
mov dword [ecx], 0x1
loc_40684D:
ret 0x4
loc_406850:
mov eax, [ecx+0x1c]
test eax, eax
jz short loc_40687B
mov eax, [esp+0x4]
push esi
mov esi, [ecx+0x20]
shr eax, 0x7
and al, 0x7f
and edx, 0xff
mov [edx+esi+0x184], al
mov ecx, [ecx+0x20]
pop esi
mov dword [ecx], 0x1
loc_40687B:
ret 0x4
align 16
loc_406880:
push ebx
push esi
mov esi, ecx
push edi
shr edx, 0x7
mov edi, [esi]
sub dl, 0x40
cmp edi, esi
mov [esi+0x56], dl
jz short loc_4068A9
loc_406894:
mov edx, edi
mov ecx, esi
call loc_409990
mov eax, [edi+0x10]
fstp dword [eax+0x70]
mov edi, [edi]
cmp edi, esi
jnz short loc_406894
loc_4068A9:
mov edi, [esi+0x8]
lea ebx, [esi+0x8]
cmp edi, ebx
jz short loc_4068C8
loc_4068B3:
mov edx, edi
mov ecx, esi
call loc_409990
mov ecx, [edi+0x10]
fstp dword [ecx+0x70]
mov edi, [edi]
cmp edi, ebx
jnz short loc_4068B3
loc_4068C8:
mov edi, [esi+0x10]
lea ebx, [esi+0x10]
cmp edi, ebx
jz short loc_4068E7
loc_4068D2:
mov edx, edi
mov ecx, esi
call loc_409990
mov edx, [edi+0x10]
fstp dword [edx+0x70]
mov edi, [edi]
cmp edi, ebx
jnz short loc_4068D2
loc_4068E7:
pop edi
pop esi
pop ebx
ret
align 16
loc_4068F0:
push ecx
and edx, 0xffff
push esi
shr edx, 0x7
sub edx, 0x40
mov esi, ecx
test edx, edx
mov [esp+0x4], edx
jle short loc_40691D
fild dword [esp+0x4]
fmul dword [loc_41B6C0]
call _ftol_asm
mov [esi+0x55], al
pop esi
pop ecx
ret
loc_40691D:
mov [esi+0x55], dl
pop esi
pop ecx
ret
align 16
loc_406930:
push ecx
push esi
mov esi, ecx
push edi
mov al, [esi+0x5e]
mov cl, [esi+0x5d]
push eax
call loc_405910
mov cl, [esi+0x5e]
xor edx, edx
cmp cl, dl
jz short loc_40699A
jbe short loc_406989
cmp cl, 0x2
ja short loc_406989
mov [esp+0x8], cl
mov [esi+0x1c], eax
mov eax, [esp+0x8]
mov [esi+0x18], edx
and eax, 0xff
mov ecx, eax
shl ecx, 0x7
add ecx, eax
lea edi, [ecx*4+loc_42A2F8]
mov [esi+0x20], edi
cmp [edi], edx
jz short loc_4069A7
mov ecx, 0x81
mov esi, loc_42A2F8
rep movsd
pop edi
pop esi
pop ecx
ret
loc_406989:
mov [esi+0x18], edx
mov [esi+0x1c], edx
mov dword [esi+0x20], loc_42A2F8
pop edi
pop esi
pop ecx
ret
loc_40699A:
mov [esi+0x18], eax
mov [esi+0x1c], edx
mov dword [esi+0x20], loc_42A2F8
loc_4069A7:
pop edi
pop esi
pop ecx
ret
align 16
loc_4069B0:
sub esp, 0x8
push ebx
push ebp
push esi
push edi
mov esi, loc_42A967
mov ebp, 0x10
loc_4069C1:
cmp byte [esi], 0x0
jz short loc_406A3F
mov ecx, [loc_42A2E8]
mov edx, [loc_42A2EC]
lea eax, [esi+0x2]
mov byte [esi], 0x0
mov [eax], ecx
mov ecx, [loc_42A2F0]
mov [eax+0x4], edx
mov edx, [loc_42A2F4]
mov [eax+0x8], ecx
mov [eax+0xc], edx
mov al, [esi+0x1]
test al, al
jz short loc_406A3F
xor edx, edx
mov byte [esi+0x1], 0x0
lea edi, [esi+0x12]
mov [esp+0x14], edx
loc_406A03:
mov al, [edi]
mov byte [edi], 0x0
inc edi
xor ebx, ebx
test al, al
mov [esp+0x13], al
jz short loc_406A35
loc_406A13:
test al, 0x1
jz short loc_406A2C
shl dl, 0x3
or dl, bl
lea ecx, [esi-0x5f]
call loc_401440
mov al, [esp+0x13]
mov edx, [esp+0x14]
loc_406A2C:
inc ebx
shr al, 1
mov [esp+0x13], al
jnz short loc_406A13
loc_406A35:
inc edx
cmp edx, 0x10
mov [esp+0x14], edx
jl short loc_406A03
loc_406A3F:
add esi, 0x104
dec ebp
jnz near loc_4069C1
pop edi
pop esi
pop ebp
pop ebx
add esp, 0x8
ret
align 16
loc_406A60:
push ebp
mov ebp, esp
sub esp, 0x30
mov [ebp-0x1c], ecx
;call timeGetTime
xor eax, eax ; the result isn't used for anything
mov edx, [loc_441848]
mov ecx, loc_441048
mov [ebp-0x20], eax
call loc_40DA90
mov edx, [loc_441848]
mov ecx, loc_441448
call loc_40DA90
mov eax, [loc_455D10]
test eax, eax
jz short loc_406AAC
mov edx, [loc_44184C]
mov ecx, [loc_455888]
call loc_40DA90
loc_406AAC:
mov eax, [loc_455D14]
test eax, eax
jz short loc_406AC6
mov edx, [loc_441848]
mov ecx, [loc_44586C]
call loc_40DA90
loc_406AC6:
push ebx
push esi
push edi
fnstcw word [loc_441024]
fldcw word [loc_41B708]
mov dword [ebp-0x4], 0x0
loc_406ADC:
mov edi, [ebp-0x4]
xor eax, eax
mov ebx, 0x3
mov al, [edi+loc_455F68]
cmp eax, ebx
ja near loc_407315
jmp dword [eax*4+loc_407AF4]
loc_406AFB:
mov al, [edi+loc_440D88]
test al, al
jz near loc_406C6B
mov al, [edi+loc_440E08]
test al, al
jnz near loc_40731C
lea ecx, [edi+edi*8]
xor esi, esi
shl ecx, 0x5
add ecx, loc_42BD88
fld dword [ecx+0xf4]
fmul dword [ecx+0xec]
mov edx, [ecx]
fadd dword [ecx+0xf8]
fstp dword [ecx+0xf8]
mov word [edx+0xaa], 0x1
mov [ecx+0xfe], bx
movsx eax, word [ecx+0xfe]
mov [ecx+0xec], esi
mov ax, [edx+eax*2+0xa4]
cmp ax, si
mov [ecx+0xfc], ax
jnz short loc_406BB2
loc_406B70:
mov ax, [ecx+0xfe]
movsx ebx, ax
inc eax
mov ebx, [edx+ebx*4+0x94]
cmp ax, 0x3
mov [ecx+0xf8], ebx
mov [ecx+0xf0], esi
mov [ecx+0xfe], ax
jge short loc_406BE7
movsx eax, ax
mov ax, [edx+eax*2+0xa4]
cmp ax, si
mov [ecx+0xfc], ax
jz short loc_406B70
loc_406BB2:
movsx eax, word [ecx+0xfe]
fld dword [edx+eax*4+0x94]
fsub dword [ecx+0xf8]
xor eax, eax
mov ax, [ecx+0xfc]
mov [ebp-0x18], eax
fstp dword [ecx+0xf4]
fild dword [ebp-0x18]
fdivr dword [loc_4189F4]
fstp dword [ecx+0xf0]
loc_406BE7:
fld dword [edx+0xb0]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
jz short loc_406C19
fld dword [edx+0xb4]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
mov eax, loc_40E270
jnz short loc_406C4F
mov eax, loc_40E390
jmp short loc_406C4F
loc_406C19:
fld dword [edx+0xb4]
fcomp dword [loc_4189F0]
cmp [loc_41B6F4], esi
fnstsw ax
jz short loc_406C40
test ah, 0x1
mov eax, loc_40E520
jnz short loc_406C4F
mov eax, loc_40E680
jmp short loc_406C4F
loc_406C40:
test ah, 0x1
mov eax, loc_40E840
jnz short loc_406C4F
mov eax, loc_40E9D0
loc_406C4F:
mov [ecx+0xe0], eax
mov dword [ecx+0xe8], loc_407FE0
mov byte [edi+loc_440E08], 0x1
jmp loc_40731C
loc_406C6B:
mov ecx, [edi*4+loc_455D68]
lea esi, [edi+edi*8]
lea eax, [edi+edi*2]
mov [ebp-0x8], ecx
shl esi, 0x5
shl eax, 0x6
add esi, loc_42BD88
lea edx, [eax+loc_434D88]
mov [esi], ecx
cmp edx, ecx
lea ecx, [eax+loc_43AD88]
jz short loc_406C9B
mov ecx, edx
loc_406C9B:
mov eax, [ebp-0x4]
mov ebx, [ebp-0x8]
xor edx, edx
add ebx, 0x32
mov [eax*4+loc_455D68], ecx
mov ecx, loc_407F10
mov byte [eax+loc_440D88], 0x0
mov [esi+0xc4], ecx
mov [esi+0xe8], ecx
mov [esi+0x8], edx
mov [esi+0x4], edx
mov ecx, [ebx+0xe]
mov [esi+0xc], ecx
lea edi, [esi+0x6c]
mov dword [ebp-0xc], 0x2
loc_406CDB:
cmp [ebx-0x12], edx
jz near loc_406E28
mov cl, [eax+loc_440D88]
inc cl
mov [eax+loc_440D88], cl
cmp [ebx-0x2], dx
mov al, cl
jz short loc_406D0A
cmp al, 0x2
mov eax, loc_40DFF0
jz short loc_406D18
mov eax, loc_40DD90
jmp short loc_406D18
loc_406D0A:
cmp al, 0x2
mov eax, loc_40D8B0
jz short loc_406D18
mov eax, loc_40D6F0
loc_406D18:
mov [edi-0x28], eax
xor eax, eax
mov [edi-0x18], edx
mov ax, [ebx]
sub eax, 0x7d00
jz short loc_406D6E
sub eax, 0x2eea
jz short loc_406D52
sub eax, 0x5a
jz short loc_406D52
cmp dword [loc_441044], 0x5622
jnz short loc_406D4A
fld dword [loc_4181E8]
jmp short loc_406D88
loc_406D4A:
fld dword [loc_4189EC]
jmp short loc_406D88
loc_406D52:
cmp dword [loc_441044], 0xac44
jnz short loc_406D66
fld dword [loc_4181E8]
jmp short loc_406D88
loc_406D66:
fld dword [loc_4189E8]
jmp short loc_406D88
loc_406D6E:
cmp dword [loc_441044], 0xac44
jnz short loc_406D82
fld dword [loc_4189E4]
jmp short loc_406D88
loc_406D82:
fld dword [loc_4189E0]
loc_406D88:
fstp dword [edi]
mov eax, [ebx-0xe]
mov [ebp-0x24], edx
mov [edi-0x20], eax
mov ecx, [ebx-0xa]
mov [ebp-0x28], ecx
mov [ebp-0x2c], edx
fild qword [ebp-0x28]
mov ecx, [ebp-0x8]
fmul dword [loc_4189DC]
fstp dword [edi-0x14]
mov eax, [ebx-0x6]
mov [ebp-0x30], eax
fild qword [ebp-0x30]
fmul dword [loc_4189DC]
fst dword [edi-0xc]
fsub dword [edi-0x14]
fstp dword [edi-0x10]
fld dword [ebx+0x2]
fadd dword [ecx+0x40]
mov [edi+0x4], edx
fstp dword [edi-0x4]
mov eax, [ebx+0xa]
mov [edi-0x24], edx
mov [edi-0x8], eax
mov eax, [ebx-0xa]
shr eax, 0x8
mov dword [edi+0x8], 0xc63b8000
jz short loc_406DF7
loc_406DE7:
fld dword [edi+0x8]
fadd dword [loc_4189E8]
sar eax, 1
fstp dword [edi+0x8]
jnz short loc_406DE7
loc_406DF7:
fld dword [esi+0x8]
fadd dword [edi]
fadd dword [edi-0x4]
fadd dword [esi+0x4]
fst dword [ebp-0x10]
fcomp dword [edi+0x8]
fnstsw ax
test ah, 0x41
jnz short loc_406E15
mov ecx, [edi+0x8]
mov [ebp-0x10], ecx
loc_406E15:
mov edx, [ebp-0x10]
push edx
call loc_40DB20
fstp dword [edi-0x1c]
mov eax, [ebp-0x4]
xor edx, edx
jmp short loc_406E2B
loc_406E28:
mov [edi-0x28], edx
loc_406E2B:
mov ecx, [ebp-0xc]
sub edi, 0x34
dec ecx
sub ebx, 0x20
cmp ecx, edx
mov [ebp-0xc], ecx
ja near loc_406CDB
mov eax, [ebp-0x8]
mov ecx, [eax+0x74]
mov [esi+0xb8], edx
mov [esi+0x94], ecx
lea ecx, [esi+0xc8]
mov [esi+0xbc], edx
mov [esi+0xd8], dx
mov [ecx], edx
mov [esi+0xda], dx
mov byte [esi+0xdc], 0x0
mov edi, [eax+0x70]
mov [esi+0x88], edi
mov [esi+0x90], edx
mov edi, [eax+0x58]
mov [esi+0xd0], edx
mov [esi+0xd4], edi
mov [esi+0x84], edx
mov dword [esi+0x98], 0xc2c80000
mov edx, [eax+0x78]
dec edx
jz short loc_406F03
dec edx
jz short loc_406EE7
dec edx
jz short loc_406ECB
mov dword [eax+0x6c], 0x3f800000
lea ebx, [esi+0x78]
mov eax, loc_407B10
mov [ebx], eax
mov [esi+0x7c], eax
mov [esi+0x80], eax
jmp short loc_406F1D
loc_406ECB:
lea ebx, [esi+0x78]
mov dword [esi+0x7c], loc_40AEB0
mov dword [esi+0x80], loc_40B280
mov dword [ebx], loc_408110
jmp short loc_406F1D
loc_406EE7:
lea ebx, [esi+0x78]
mov dword [esi+0x7c], loc_40B000
mov dword [esi+0x80], loc_40B3C0
mov dword [ebx], loc_408180
jmp short loc_406F1D
loc_406F03:
lea ebx, [esi+0x78]
mov dword [esi+0x7c], loc_40AEB0
mov dword [esi+0x80], loc_40B140
mov dword [ebx], loc_408090
loc_406F1D:
mov edi, [ebp-0x8]
fld dword [loc_4189D8]
fdiv dword [edi+0x6c]
lea edx, [edi+0x4c]
fstp dword [esi+0xc0]
call loc_408010
fld dword [edi+0x68]
fmul dword [esi+0xd4]
mov ecx, ebx
mov dword [esi+0xa0], 0xc47a0000
fstp dword [esi+0x8c]
call loc_4081E0
mov ecx, ebx
call dword [ebx]
mov edx, [esi+0x9c]
lea ecx, [esi+0xec]
mov [esi+0xa0], edx
xor eax, eax
lea edx, [edi+0x94]
mov [esi+0x84], eax
mov [esi+0xfc], ax
mov [ecx], eax
mov [esi+0xf8], eax
mov [esi+0xf4], eax
mov [esi+0x100], al
mov [esi+0xfe], ax
call loc_408010
lea edx, [edi+0x7c]
lea ecx, [esi+0xe0]
call loc_407EA0
fld dword [edi+0x90]
fmul dword [esi+0xf8]
lea edx, [edi+0xb8]
lea ecx, [esi+0x104]
fstp dword [esi+0xe4]
call loc_4082D0
mov eax, [ebp-0x4]
mov edi, eax
mov byte [eax+loc_440E08], 0x0
mov byte [eax+loc_455F68], 0x0
jmp loc_40731C
loc_406FEB:
mov al, [edi+loc_440D88]
test al, al
jz near loc_407315
mov al, [edi+loc_440E08]
test al, al
jnz near loc_407315
lea ecx, [edi+edi*8]
xor esi, esi
shl ecx, 0x5
add ecx, loc_42BD88
fld dword [ecx+0xf4]
fmul dword [ecx+0xec]
mov eax, [ecx]
mov [ecx+0xfe], bx
add eax, 0x94
fadd dword [ecx+0xf8]
fstp dword [ecx+0xf8]
movsx edx, word [ecx+0xfe]
mov [ecx+0xec], esi
mov dx, [eax+edx*2+0x10]
cmp dx, si
mov [ecx+0xfc], dx
jnz short loc_407098
loc_407059:
mov dx, [ecx+0xfe]
movsx ebx, dx
inc edx
mov ebx, [eax+ebx*4]
mov [ecx+0xf0], esi
mov [ecx+0xf8], ebx
mov ebx, 0x3
cmp dx, bx
mov [ecx+0xfe], dx
jge short loc_4070C9
movsx edx, dx
mov dx, [eax+edx*2+0x10]
cmp dx, si
mov [ecx+0xfc], dx
jz short loc_407059
loc_407098:
movsx edx, word [ecx+0xfe]
fld dword [eax+edx*4]
fsub dword [ecx+0xf8]
xor eax, eax
mov ax, [ecx+0xfc]
mov [ebp-0x18], eax
fstp dword [ecx+0xf4]
fild dword [ebp-0x18]
fdivr dword [loc_4189F4]
fstp dword [ecx+0xf0]
loc_4070C9:
mov edx, [ecx]
add edx, 0x7c
fld dword [edx+0x34]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
jz short loc_4070FA
fld dword [edx+0x38]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
mov eax, loc_40E270
jnz short loc_40712D
mov eax, loc_40E390
jmp short loc_40712D
loc_4070FA:
fld dword [edx+0x38]
fcomp dword [loc_4189F0]
cmp [loc_41B6F4], esi
fnstsw ax
jz short loc_40711E
test ah, 0x1
mov eax, loc_40E520
jnz short loc_40712D
mov eax, loc_40E680
jmp short loc_40712D
loc_40711E:
test ah, 0x1
mov eax, loc_40E840
jnz short loc_40712D
mov eax, loc_40E9D0
loc_40712D:
mov [ecx+0xe0], eax
cmp [ecx+0xfc], si
jnz short loc_407143
mov byte [ecx+0x100], 0x1
loc_407143:
fld dword [ecx+0xd0]
fmul dword [ecx+0xc8]
mov eax, [ecx]
mov dword [ecx+0xe8], loc_407FE0
mov [ecx+0xda], bx
add eax, 0x4c
fadd dword [ecx+0xd4]
fstp dword [ecx+0xd4]
movsx edx, word [ecx+0xda]
mov [ecx+0xc8], esi
mov dx, [eax+edx*2+0x10]
cmp dx, si
mov [ecx+0xd8], dx
jnz short loc_4071CA
loc_40718F:
mov dx, [ecx+0xda]
movsx ebx, dx
inc edx
mov ebx, [eax+ebx*4]
cmp dx, 0x3
mov [ecx+0xd4], ebx
mov [ecx+0xcc], esi
mov [ecx+0xda], dx
jge short loc_4071FB
movsx edx, dx
mov dx, [eax+edx*2+0x10]
cmp dx, si
mov [ecx+0xd8], dx
jz short loc_40718F
loc_4071CA:
movsx edx, word [ecx+0xda]
fld dword [eax+edx*4]
fsub dword [ecx+0xd4]
xor eax, eax
mov ax, [ecx+0xd8]
mov [ebp-0x18], eax
fstp dword [ecx+0xd0]
fild dword [ebp-0x18]
fdivr dword [loc_4189F4]
fstp dword [ecx+0xcc]
loc_4071FB:
mov dword [ecx+0xc4], loc_407FE0
jmp loc_407315
loc_40720A:
mov al, [edi+loc_440D88]
test al, al
jz near loc_407315
mov al, [edi+loc_440E08]
test al, al
jnz near loc_407315
lea esi, [edi+edi*8]
xor edx, edx
shl esi, 0x5
add esi, loc_42BD88
fld dword [esi+0xf4]
fmul dword [esi+0xec]
mov eax, [esi]
fadd dword [esi+0xf8]
fstp dword [esi+0xf8]
mov word [eax+0xaa], 0x1
mov [esi+0xfe], bx
movsx ecx, word [esi+0xfe]
mov [esi+0xec], edx
mov cx, [eax+ecx*2+0xa4]
cmp cx, dx
mov [esi+0xfc], cx
jnz short loc_4072C1
loc_40727F:
mov cx, [esi+0xfe]
movsx ebx, cx
inc ecx
mov ebx, [eax+ebx*4+0x94]
cmp cx, 0x3
mov [esi+0xf8], ebx
mov [esi+0xf0], edx
mov [esi+0xfe], cx
jge short loc_4072F6
movsx ecx, cx
mov cx, [eax+ecx*2+0xa4]
cmp cx, dx
mov [esi+0xfc], cx
jz short loc_40727F
loc_4072C1:
movsx edx, word [esi+0xfe]
xor ecx, ecx
fld dword [eax+edx*4+0x94]
fsub dword [esi+0xf8]
mov cx, [esi+0xfc]
mov [ebp-0x18], ecx
fstp dword [esi+0xf4]
fild dword [ebp-0x18]
fdivr dword [loc_4189F4]
fstp dword [esi+0xf0]
loc_4072F6:
lea edx, [eax+0x7c]
lea ecx, [esi+0xe0]
call loc_407EA0
mov dword [esi+0xe8], loc_407FE0
mov byte [edi+loc_440E08], 0x1
loc_407315:
mov byte [edi+loc_455F68], 0x0
loc_40731C:
mov al, [edi+loc_440D88]
mov esi, [ebp-0x4]
test al, al
jz near loc_4076D5
lea esi, [esi+esi*8]
mov dword [ebp-0x8], 0x0
shl esi, 0x5
add esi, loc_42BD88
mov ebx, [esi]
lea edi, [esi+0xc8]
mov ecx, edi
lea edx, [ebx+0x4c]
call dword [esi+0xc4]
fld dword [esi+0xd0]
fmul dword [edi]
mov ax, [esi+0x108]
lea edi, [esi+0x104]
test ax, ax
fadd dword [esi+0xd4]
fstp dword [ebp-0x10]
jz short loc_40737D
dec eax
mov [edi+0x4], ax
jmp short loc_407394
loc_40737D:
mov ax, [edi+0x6]
test ax, ax
jz short loc_407394
fld dword [edi+0xc]
fadd dword [edi+0x8]
dec eax
mov [edi+0x6], ax
fstp dword [edi+0x8]
loc_407394:
mov ecx, edi
call dword [edi]
fmul dword [edi+0x8]
fstp dword [edi+0x10]
fld dword [ebx+0x44]
fmul dword [esi+0x114]
fcom dword [esi+0x8]
fnstsw ax
test ah, 0x40
jnz short loc_4073BD
fstp dword [esi+0x8]
mov dword [ebp-0x8], 0x1
jmp short loc_4073BF
loc_4073BD:
fstp st0
loc_4073BF:
fld dword [ebp-0x10]
fmul dword [ebx+0x48]
fcom dword [esi+0x4]
fnstsw ax
test ah, 0x40
jnz short loc_4073DB
fstp dword [esi+0x4]
mov dword [ebp-0x8], 0x1
jmp short loc_4073DD
loc_4073DB:
fstp st0
loc_4073DD:
fld dword [esi+0xc]
fcomp dword [ebx+0x40]
fnstsw ax
test ah, 0x40
jnz short loc_407406
fld dword [ebx+0x40]
mov dword [ebp-0x8], 0x1
fst dword [esi+0xc]
fadd dword [ebx+0x14]
fstp dword [esi+0x34]
fld dword [ebx+0x34]
fadd dword [esi+0xc]
fstp dword [esi+0x68]
loc_407406:
lea ecx, [ebx+0x20]
mov dword [ebp-0xc], 0x1
mov [ebp-0x18], ecx
lea edi, [esi+0x48]
loc_407416:
mov eax, [edi-0x4]
test eax, eax
jz near loc_4074D5
cmp dword [edi], 0x0
jnz short loc_407496
fld dword [edi+0xc]
fcomp dword [edi+0x14]
fnstsw ax
test ah, 0x1
jnz short loc_407496
cmp dword [ecx], 0x1
jnz short loc_407481
mov eax, [ebp-0x4]
mov dword [edi-0x4], 0x0
mov cl, [eax+loc_440D88]
dec cl
mov [eax+loc_440D88], cl
jz near loc_4076B6
mov eax, [ebp-0xc]
test eax, eax
jz short loc_407471
cmp word [ebx+0x10], 0x0
mov eax, loc_40DD90
jnz short loc_40746E
mov eax, loc_40D6F0
loc_40746E:
mov [esi+0x10], eax
loc_407471:
mov edx, [ebp-0xc]
mov ecx, [ebp-0x4]
push edx
mov edx, ebx
call loc_40A670
jmp short loc_4074D5
loc_407481:
mov dword [edi], 0x1
mov eax, [ecx+0x18]
mov [edi+0x28], eax
mov dword [ebp-0x8], 0x1
jmp short loc_40749D
loc_407496:
mov eax, [ebp-0x8]
test eax, eax
jz short loc_4074CB
loc_40749D:
fld dword [edi+0x28]
fadd dword [edi+0x24]
fadd dword [edi+0x20]
fadd dword [esi+0x8]
fadd dword [esi+0x4]
fst dword [ebp-0x14]
fcomp dword [edi+0x2c]
fnstsw ax
test ah, 0x41
jnz short loc_4074BF
mov ecx, [edi+0x2c]
mov [ebp-0x14], ecx
loc_4074BF:
mov edx, [ebp-0x14]
push edx
call loc_40DB20
fstp dword [edi+0x8]
loc_4074CB:
lea ecx, [edi-0x4]
mov edx, loc_455904
call dword [ecx]
loc_4074D5:
mov eax, [ebp-0xc]
mov ecx, [ebp-0x18]
mov edx, eax
dec eax
sub edi, 0x34
sub ecx, 0x20
test edx, edx
mov [ebp-0xc], eax
mov [ebp-0x18], ecx
jnz near loc_407416
mov eax, [ebx+0x78]
test eax, eax
jz near loc_407591
fld dword [esi+0x88]
fcomp dword [ebx+0x70]
xor ecx, ecx
fnstsw ax
test ah, 0x40
jnz short loc_40751D
mov eax, [ebx+0x70]
mov ecx, 0x1
mov [esi+0x88], eax
loc_40751D:
fld dword [ebp-0x10]
fmul dword [ebx+0x68]
fcom dword [esi+0x8c]
fnstsw ax
test ah, 0x40
jnz short loc_40753D
fstp dword [esi+0x8c]
mov ecx, 0x1
jmp short loc_40753F
loc_40753D:
fstp st0
loc_40753F:
fld dword [ebx+0x64]
fmul dword [esi+0x114]
fcom dword [esi+0x90]
fnstsw ax
test ah, 0x40
jnz short loc_40755D
fstp dword [esi+0x90]
jmp short loc_407563
loc_40755D:
test ecx, ecx
fstp st0
jz short loc_40758B
loc_407563:
lea edi, [esi+0x78]
mov ecx, edi
call loc_4081E0
test eax, eax
jz short loc_40757F
mov eax, [esi+0x84]
mov ecx, edi
test eax, eax
jnz short loc_407583
call dword [edi]
loc_40757F:
mov ecx, edi
jmp short loc_40758E
loc_407583:
call dword [esi+0x80]
jmp short loc_407591
loc_40758B:
lea ecx, [esi+0x78]
loc_40758E:
call dword [esi+0x7c]
loc_407591:
lea edi, [esi+0xec]
lea edx, [ebx+0x94]
mov ecx, edi
call dword [esi+0xe8]
test eax, eax
jz short loc_407618
fld dword [ebx+0xb0]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
jz short loc_4075DB
fld dword [ebx+0xb4]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
mov eax, loc_40E270
jnz short loc_407612
mov eax, loc_40E390
jmp short loc_407612
loc_4075DB:
fld dword [ebx+0xb4]
fcomp dword [loc_4189F0]
mov eax, [loc_41B6F4]
test eax, eax
fnstsw ax
jz short loc_407603
test ah, 0x1
mov eax, loc_40E520
jnz short loc_407612
mov eax, loc_40E680
jmp short loc_407612
loc_407603:
test ah, 0x1
mov eax, loc_40E840
jnz short loc_407612
mov eax, loc_40E9D0
loc_407612:
mov [esi+0xe0], eax
loc_407618:
cmp word [esi+0xfe], 0x2
jg short loc_40762C
fld dword [esi+0xf4]
fmul dword [edi]
jmp short loc_407644
loc_40762C:
fld dword [loc_4189F4]
fsub dword [edi]
fld st0
fmulp st1, st0
fsubr dword [loc_4189F4]
fmul dword [esi+0xf4]
loc_407644:
fadd dword [esi+0xf8]
fld dword [esi+0x114]
fsub dword [loc_4189F4]
mov eax, [ebx+0x7c]
lea edx, [ebx+0x7c]
test eax, eax
fmul dword [ebx+0xac]
fmul dword [loc_4189D4]
fadd dword [loc_4189F4]
fmul st0, st1
fstp dword [ebp-0x10]
fstp st0
jz short loc_4076A0
fld dword [ebx+0x80]
fadd dword [ebx+0x88]
dec eax
mov [edx], eax
fstp dword [ebx+0x88]
fld dword [ebx+0x84]
fadd dword [ebx+0x8c]
fstp dword [ebx+0x8c]
loc_4076A0:
mov eax, [ebp-0x10]
lea ecx, [esi+0xe0]
push eax
call dword [ecx]
mov al, [esi+0x100]
test al, al
jz short loc_4076D2
loc_4076B6:
mov esi, [ebp-0x4]
mov edx, ebx
mov ecx, esi
mov byte [esi+loc_440D88], 0x0
mov byte [esi+loc_440E08], 0x0
call loc_40A660
jmp short loc_4076D5
loc_4076D2:
mov esi, [ebp-0x4]
loc_4076D5:
inc esi
cmp esi, 0x80
mov [ebp-0x4], esi
jl near loc_406ADC
mov eax, [loc_455D14]
test eax, eax
jz near loc_407885
mov al, [loc_455D60]
test al, al
jz near loc_40782F
xor ecx, ecx
mov byte [loc_455D60], 0x0
mov cl, [loc_455D63]
mov [ebp-0x18], ecx
fild dword [ebp-0x18]
fmul dword [loc_41B6CC]
fmul dword [loc_4189D0]
fstp dword [ebp-0x18]
fld dword [ebp-0x18]
fistp dword [ebp-0x14]
xor eax, eax
mov ecx, [loc_455D64]
mov al, [loc_455D65]
mov edx, [ebp-0x14]
mov [ebp-0x18], eax
and ecx, 0xff
fild dword [ebp-0x18]
mov [ebp-0x18], ecx
inc edx
mov [loc_445860], edx
xor edx, edx
fmul dword [loc_41B6CC]
mov dl, [loc_455D62]
xor eax, eax
mov al, [loc_455D66]
xor ecx, ecx
fmul dword [loc_4189CC]
mov cl, [loc_455D61]
fadd dword [loc_4189C8]
fst dword [loc_445878]
fmul dword [loc_4189D4]
fstp dword [loc_445870]
fld dword [loc_41B6CC]
fmul dword [loc_4189C4]
fdivr dword [loc_4189C0]
fimul dword [ebp-0x18]
mov [ebp-0x18], edx
fmul dword [loc_445878]
fstp dword [loc_445874]
fild dword [ebp-0x18]
mov [ebp-0x18], eax
fmul dword [loc_4189BC]
fstp dword [loc_445880]
fild dword [ebp-0x18]
mov [ebp-0x18], ecx
fmul dword [loc_4189B8]
fstp dword [loc_445884]
fild dword [ebp-0x18]
fmul dword [loc_4181E0]
fstp dword [loc_44587C]
fld dword [loc_445878]
fistp dword [ebp-0x18]
mov edx, [ebp-0x18]
mov eax, [loc_445860]
lea ecx, [eax+edx+0x1]
mov al, [loc_455D62]
test al, al
mov [loc_445858], ecx
jz short loc_40781B
mov dword [loc_445864], loc_40B5F0
mov dword [loc_445868], loc_40B4F0
jmp short loc_40782F
loc_40781B:
mov dword [loc_445864], loc_40B790
mov dword [loc_445868], loc_40B6C0
loc_40782F:
mov edx, [loc_445858]
mov eax, [loc_44585C]
cmp edx, eax
mov dword [loc_41B704], 0x1
jae short loc_407850
call dword [loc_445864]
jmp short loc_407860
loc_407850:
mov eax, [loc_441850]
mov [loc_445850], eax
call dword [loc_445868]
loc_407860:
mov ecx, [loc_441848]
mov edx, [loc_44585C]
lea eax, [edx+ecx]
and eax, 0xfff
mov [loc_44585C], eax
lea eax, [eax*4+loc_441850]
mov [loc_44586C], eax
loc_407885:
mov eax, [loc_455D10]
test eax, eax
jz near loc_407965
mov eax, [loc_455D18]
test eax, eax
jz short loc_4078A0
call loc_408A20
loc_4078A0:
mov esi, [loc_455888]
mov ecx, [loc_45589C]
mov edx, [loc_4558A0]
sub esi, loc_445888
mov eax, [loc_455898]
mov dword [loc_41B700], 0x1
sar esi, 0x2
add eax, esi
lea edi, [ecx+esi]
mov ecx, esi
and edi, 0x3fff
lea ebx, [edx+edi]
and ebx, 0x3fff
test eax, 0xffffc000
jz short loc_4078F9
call loc_40B850
mov edx, edi
mov ecx, esi
push ebx
call dword [loc_44102C]
jmp short loc_40794B
loc_4078F9:
call loc_40BA10
mov eax, [loc_44184C]
mov edx, [loc_4558CC]
add edx, edi
lea ecx, [edi+eax]
or ecx, edx
test ecx, 0xffffc000
jz short loc_407925
push ebx
mov edx, edi
mov ecx, esi
call dword [loc_441030]
jmp short loc_40794B
loc_407925:
mov ecx, [loc_4558B4]
add eax, ebx
add ecx, ebx
push ebx
or eax, ecx
mov edx, edi
test eax, 0xffffc000
mov ecx, esi
jz short loc_407945
call dword [loc_441034]
jmp short loc_40794B
loc_407945:
call dword [loc_441038]
loc_40794B:
mov edx, [loc_44184C]
add esi, edx
and esi, 0x3fff
lea eax, [esi*4+loc_445888]
mov [loc_455888], eax
loc_407965:
mov ecx, [ebp-0x1c]
call loc_40D600
;call timeGetTime
xor eax, eax ; the result isn't used for anything
mov edi, [ebp-0x20]
mov esi, [loc_44101C]
sub eax, edi
add esi, eax
mov eax, [loc_441020]
mov ecx, eax
dec eax
test ecx, ecx
mov [loc_44101C], esi
mov [loc_441020], eax
jnz near loc_407AEA
mov edx, esi
xor eax, eax
mov [ebp-0x30], edx
mov [ebp-0x2c], eax
fild qword [ebp-0x30]
mov [loc_44101C], eax
mov dword [loc_441020], 0xf
fmul dword [loc_4189B4]
fstp dword [loc_441028]
fld dword [loc_441028]
fcomp dword [loc_441040]
fnstsw ax
test ah, 0x1
jnz near loc_407A99
mov eax, [loc_41B6D4]
dec eax
mov [loc_41B6D4], eax
jnz near loc_407AEA
fld dword [loc_441028]
fcomp dword [loc_4189F4]
fnstsw ax
test ah, 0x1
jz short loc_407A26
fld dword [loc_441028]
fsub dword [loc_441040]
fmul dword [loc_4189C8]
fstp dword [ebp-0x20]
fld dword [ebp-0x20]
fistp dword [ebp-0x1c]
mov eax, [ebp-0x1c]
lea ecx, [eax+0x1]
call loc_402240
jmp short loc_407A74
loc_407A26:
mov eax, [loc_41B6D8]
dec eax
mov [loc_41B6D8], eax
jz short loc_407A59
fld dword [loc_441028]
fsub dword [loc_441040]
fmul dword [loc_4189C8]
fstp dword [ebp-0x20]
fld dword [ebp-0x20]
fistp dword [ebp-0x1c]
mov ecx, [ebp-0x1c]
inc ecx
call loc_402240
jmp short loc_407A7E
loc_407A59:
fld dword [loc_4189F4]
fdiv dword [loc_441028]
push ecx
fsubr dword [loc_4189F4]
fstp dword [esp]
call loc_402410
loc_407A74:
mov dword [loc_41B6D8], 0x3
loc_407A7E:
pop edi
pop esi
mov dword [loc_41B6DC], 0x6
mov dword [loc_41B6D4], 0x4
pop ebx
mov esp, ebp
pop ebp
ret
loc_407A99:
fld dword [loc_441028]
fcomp dword [loc_44103C]
fnstsw ax
test ah, 0x1
jnz short loc_407AB5
xor ecx, ecx
call loc_402240
jmp short loc_407ACC
loc_407AB5:
mov eax, [loc_41B6DC]
dec eax
mov [loc_41B6DC], eax
jnz short loc_407AD6
mov ecx, 0x1
call loc_4021B0
loc_407ACC:
mov dword [loc_41B6DC], 0x6
loc_407AD6:
mov dword [loc_41B6D4], 0x4
mov dword [loc_41B6D8], 0x3
loc_407AEA:
pop edi
pop esi
pop ebx
mov esp, ebp
pop ebp
ret
align 4
loc_407AF4:
dd loc_40731C
dd loc_406AFB
dd loc_406FEB
dd loc_40720A
align 4
align 16
loc_407B10:
ret
align 16
loc_407B20:
push ebx
push ebp
push esi
mov esi, [esp+0x14]
mov [loc_44103C], esi
mov esi, [esp+0x10]
mov eax, 0x1
xor ebp, ebp
mov [loc_41B6E0], edx
cmp ecx, 0xac44
push edi
mov [loc_41B6F8], eax
mov dword [loc_41B6D8], 0x3
mov dword [loc_41B6D4], 0x4
mov dword [loc_441020], 0xf
mov dword [loc_41B6DC], 0x6
mov [loc_441040], esi
mov edx, 0x80
jz short loc_407BB5
mov [loc_41B6F4], ebp
mov dword [loc_41B6CC], 0x46ac4400
mov [loc_441848], edx
mov dword [loc_455D04], 0x3c800000
mov dword [loc_455D0C], 0x10
mov dword [loc_441044], 0x5622
jmp short loc_407BEC
loc_407BB5:
mov [loc_41B6F4], eax
mov dword [loc_41B6CC], 0x472c4400
mov dword [loc_441848], 0x100
mov dword [loc_455D04], 0x3c000000
mov dword [loc_455D0C], 0x20
mov dword [loc_441044], 0xac44
loc_407BEC:
fld dword [loc_41B6CC]
fmul dword [loc_4189D4]
mov [loc_41B6EC], eax
mov eax, [loc_41B700]
cmp eax, ebp
mov dword [loc_455D08], 0x3e000000
fsub dword [loc_418A00]
mov [loc_44184C], edx
mov [loc_44101C], ebp
mov dword [loc_441028], 0x0
mov byte [loc_41B6E8], 0x4
fstp dword [loc_41B6D0]
jz short loc_407C4E
mov edx, 0x4000
mov ecx, loc_445888
call loc_40DA90
mov [loc_41B700], ebp
loc_407C4E:
mov eax, [loc_41B6F4]
mov ecx, 0x12
mov esi, loc_4188D8
mov edi, loc_455D18
cmp eax, ebp
mov [loc_41B6EC], ebp
rep movsd
jz short loc_407C98
mov dword [loc_44102C], loc_40BB60
mov dword [loc_441030], loc_40BD10
mov dword [loc_441034], loc_40BF20
mov dword [loc_441038], loc_40C130
jmp short loc_407CC0
loc_407C98:
mov dword [loc_44102C], loc_40C950
mov dword [loc_441030], loc_40CAE0
mov dword [loc_441034], loc_40CCC0
mov dword [loc_441038], loc_40CEA0
loc_407CC0:
call loc_408A20
mov [esp+0x18], ebp
mov eax, loc_440E88
loc_407CCE:
fild dword [esp+0x18]
mov esi, [esp+0x18]
add eax, 0x4
inc esi
cmp eax, loc_441018
fmul dword [loc_4189FC]
mov [esp+0x18], esi
fmul dword [loc_4189F8]
fsin
fstp dword [eax-0x4]
jl short loc_407CCE
mov eax, [loc_440E88]
push ebp
mov [loc_441018], eax
;call time
xor eax, eax ; the result isn't used for anything
xor ebx, ebx
add esp, 0x4
mov bl, [loc_4189AE]
mov ecx, loc_441850
cmp ebx, 0x6
mov [loc_44586C], ecx
mov [loc_44585C], ebp
mov byte [loc_41B6F0], 0xff
jae short loc_407D93
cmp ebx, 0xff
jz short loc_407D7F
mov eax, [loc_41B704]
mov [loc_41B6F0], bl
cmp eax, ebp
jz short loc_407D55
mov edx, 0x1000
call loc_40DA90
mov [loc_41B704], ebp
loc_407D55:
lea ecx, [ebx*8]
sub ecx, ebx
add ecx, loc_418980
mov edx, [ecx]
mov [loc_455D60], edx
mov ax, [ecx+0x4]
mov [loc_455D64], ax
mov cl, [ecx+0x6]
mov [loc_455D66], cl
loc_407D7F:
lea edx, [ebx*8]
sub edx, ebx
mov al, [edx+loc_418981]
mov [loc_455D61], al
loc_407D93:
fld dword [loc_4181E8]
mov eax, loc_42BA10
loc_407D9E:
fld st0
fmul dword [loc_4189F8]
add eax, 0x4
cmp eax, loc_42BD88
fdiv dword [loc_41B6CC]
fptan
fstp st0
fstp dword [eax-0x4]
fadd dword [loc_418A00]
jl short loc_407D9E
mov ecx, 0x20
xor eax, eax
mov edi, loc_440E08
mov esi, loc_455D68
rep stosd
fstp st0
mov ecx, 0x20
mov edi, loc_440D88
rep stosd
mov ecx, 0x20
mov edi, loc_455F68
mov edx, loc_434D88
rep stosd
loc_407DF5:
mov [esi], edx
add edx, 0xc0
add esi, 0x4
cmp edx, loc_43AD88
jl short loc_407DF5
pop edi
pop esi
pop ebp
pop ebx
ret 0x8
loc_407E60:
fld dword [esp+0x8]
fcomp dword [loc_4189F4]
fnstsw ax
test ah, 0x41
jnz short loc_407E79
mov dword [esp+0x8], 0x3f800000
loc_407E79:
fld dword [esp+0x4]
fcom dword [esp+0x8]
fnstsw ax
test ah, 0x41
jnz short loc_407E8E
fstp st0
fld dword [esp+0x8]
loc_407E8E:
mov eax, [esp+0x8]
fstp dword [loc_44103C]
mov [loc_441040], eax
ret 0x8
loc_407EA0:
fld dword [edx+0x34]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
jz short loc_407ECD
fld dword [edx+0x38]
fcomp dword [loc_4189F0]
fnstsw ax
test ah, 0x1
mov eax, loc_40E270
jnz short loc_407F02
mov eax, loc_40E390
mov [ecx], eax
ret
loc_407ECD:
fld dword [edx+0x38]
fcomp dword [loc_4189F0]
mov eax, [loc_41B6F4]
test eax, eax
fnstsw ax
jz short loc_407EF3
test ah, 0x1
mov eax, loc_40E520
jnz short loc_407F02
mov eax, loc_40E680
mov [ecx], eax
ret
loc_407EF3:
test ah, 0x1
mov eax, loc_40E840
jnz short loc_407F02
mov eax, loc_40E9D0
loc_407F02:
mov [ecx], eax
ret
align 16
loc_407F10:
push ecx
mov ax, [ecx+0x12]
push esi
cmp ax, 0x3
jge near loc_407FCD
fld dword [ecx]
fadd dword [ecx+0x4]
dec word [ecx+0x10]
mov si, [ecx+0x10]
test si, si
fstp dword [ecx]
jnz near loc_407FCD
inc eax
cmp ax, 0x3
mov [ecx+0x12], ax
jge short loc_407FB9
fld dword [ecx+0x8]
fadd dword [ecx+0xc]
movsx esi, ax
fstp dword [ecx+0xc]
push edi
mov dword [ecx], 0x0
mov di, [edx+esi*2+0x10]
test di, di
mov [ecx+0x10], di
jnz short loc_407F8D
loc_407F64:
mov esi, [edx+esi*4]
inc eax
cmp ax, 0x3
mov [ecx+0xc], esi
mov dword [ecx+0x4], 0x0
mov [ecx+0x12], ax
jge short loc_407FB0
movsx esi, ax
mov di, [edx+esi*2+0x10]
test di, di
mov [ecx+0x10], di
jz short loc_407F64
loc_407F8D:
movsx eax, ax
fld dword [edx+eax*4]
fsub dword [ecx+0xc]
xor edx, edx
mov dx, [ecx+0x10]
mov [esp+0x8], edx
fstp dword [ecx+0x8]
fild dword [esp+0x8]
fdivr dword [loc_4189F4]
fstp dword [ecx+0x4]
loc_407FB0:
pop edi
mov eax, 0x1
pop esi
pop ecx
ret
loc_407FB9:
fld dword [edx+0x8]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x40
jz short loc_407FCD
mov byte [ecx+0x14], 0x1
loc_407FCD:
xor eax, eax
pop esi
pop ecx
ret
align 16
loc_407FE0:
mov al, [ecx+0x14]
test al, al
jnz short loc_408005
mov ax, [ecx+0x10]
test ax, ax
jz short loc_408001
fld dword [ecx+0x4]
fadd dword [ecx]
dec eax
test ax, ax
mov [ecx+0x10], ax
fstp dword [ecx]
jnz short loc_408005
loc_408001:
mov byte [ecx+0x14], 0x1
loc_408005:
xor eax, eax
ret
align 16
loc_408010:
push ecx
movsx eax, word [ecx+0x12]
mov dword [ecx], 0x0
push edi
mov ax, [edx+eax*2+0x10]
test ax, ax
mov [ecx+0x10], ax
jnz short loc_40805A
loc_40802A:
mov ax, [ecx+0x12]
movsx edi, ax
inc eax
mov edi, [edx+edi*4]
cmp ax, 0x3
mov [ecx+0xc], edi
mov dword [ecx+0x4], 0x0
mov [ecx+0x12], ax
jge short loc_40807E
movsx eax, ax
mov ax, [edx+eax*2+0x10]
test ax, ax
mov [ecx+0x10], ax
jz short loc_40802A
loc_40805A:
movsx eax, word [ecx+0x12]
fld dword [edx+eax*4]
fsub dword [ecx+0xc]
xor edx, edx
mov dx, [ecx+0x10]
mov [esp+0x4], edx
fstp dword [ecx+0x8]
fild dword [esp+0x4]
fdivr dword [loc_4189F4]
fstp dword [ecx+0x4]
loc_40807E:
pop edi
pop ecx
ret
align 16
loc_408090:
sub esp, 0xc
fld dword [ecx+0x24]
fld st0
fmul st0, st1
fmul dword [loc_418A08]
fstp dword [esp]
fmul dword [ecx+0x48]
fld st0
fadd dword [esp]
fadd dword [loc_418A08]
fdivr dword [loc_4189F4]
fstp dword [esp+0x4]
fld dword [esp]
fadd st0, st0
fstp dword [esp+0x8]
fld dword [loc_418A04]
fsub dword [esp+0x8]
fmul dword [esp+0x4]
fstp dword [ecx+0x38]
fsub dword [esp]
fsub dword [loc_418A08]
fmul dword [esp+0x4]
fstp dword [ecx+0x3c]
fld dword [esp+0x4]
fmul dword [esp]
fstp dword [ecx+0x2c]
fld dword [esp+0x8]
fmul dword [esp+0x4]
fstp dword [ecx+0x30]
add esp, 0xc
ret
align 16
loc_408110:
sub esp, 0x8
fld dword [ecx+0x24]
fld st0
fmul st0, st1
fmul dword [loc_418A08]
fstp dword [esp+0x4]
fmul dword [ecx+0x48]
fld st0
fadd dword [esp+0x4]
fadd dword [loc_418A08]
fdivr dword [loc_4189F4]
fstp dword [esp]
fld dword [esp+0x4]
fadd st0, st0
fsubr dword [loc_418A04]
fmul dword [esp]
fstp dword [ecx+0x38]
fsub dword [esp+0x4]
fsub dword [loc_418A08]
fmul dword [esp]
fstp dword [ecx+0x3c]
fld dword [esp]
fmul dword [loc_418A08]
fstp dword [ecx+0x2c]
fld dword [esp]
fmul dword [loc_418A0C]
fstp dword [ecx+0x30]
add esp, 0x8
ret
align 16
loc_408180:
push ecx
fld dword [ecx+0x24]
fld st0
fmul st0, st1
fmul dword [loc_418A08]
fstp dword [esp]
fmul dword [ecx+0x48]
fld st0
fadd dword [esp]
fadd dword [loc_418A08]
fdivr dword [loc_4189F4]
fld dword [esp]
fadd st0, st0
fsubr dword [loc_418A04]
fmul st0, st1
fstp dword [ecx+0x38]
fld st1
fsub dword [esp]
fsub dword [loc_418A08]
fmul st0, st1
fstp dword [ecx+0x3c]
fmulp st1, st0
fst dword [ecx+0x2c]
fmul dword [loc_418A10]
fstp dword [ecx+0x34]
pop ecx
ret
align 16
loc_4081E0:
push ebp
mov ebp, esp
sub esp, 0x10
push esi
mov esi, ecx
push ecx
fld dword [esi+0x1c]
fadd dword [esi+0x18]
fadd dword [esi+0x14]
fstp dword [esp]
call loc_40DB20
fmul dword [esi+0x10]
fst dword [ebp-0x4]
fcomp dword [loc_41B6D0]
fnstsw ax
test ah, 0x41
jnz short loc_408218
mov eax, [loc_41B6D0]
mov [ebp-0x4], eax
jmp short loc_40822F
loc_408218:
fld dword [ebp-0x4]
fcomp dword [loc_418A14]
fnstsw ax
test ah, 0x1
jz short loc_40822F
mov dword [ebp-0x4], 0x41a00000
loc_40822F:
fld dword [ebp-0x4]
fsub dword [esi+0x20]
fstp dword [ebp-0x8]
fld dword [ebp-0x8]
fabs
fstp dword [ebp-0x8]
fld dword [ebp-0x8]
fcomp dword [loc_418A00]
fnstsw ax
test ah, 0x41
jnz short loc_4082B1
mov dword [esi+0xc], 0x1
loc_408257:
fld dword [ebp-0x4]
fmul dword [loc_4189F0]
mov ecx, [ebp-0x4]
mov [esi+0x20], ecx
fstp dword [ebp-0x8]
fld dword [ebp-0x8]
fistp dword [ebp-0xc]
mov eax, [ebp-0xc]
mov dword [ebp-0xc], 0x0
mov [ebp-0x10], eax
fld dword [eax*4+loc_42BA10]
fild qword [ebp-0x10]
fmul dword [loc_418A00]
fsubr dword [ebp-0x4]
fmul dword [loc_4189F0]
fld dword [eax*4+loc_42BA14]
fsub st0, st2
mov eax, 0x1
fmulp st1, st0
fadd st0, st1
fstp dword [esi+0x24]
pop esi
fstp st0
mov esp, ebp
pop ebp
ret
loc_4082B1:
fld dword [ebp-0x4]
fcomp dword [esi+0x20]
fnstsw ax
test ah, 0x40
jz short loc_408257
xor eax, eax
pop esi
mov esp, ebp
pop ebp
ret
align 16
loc_4082D0:
push ecx
xor eax, eax
mov dword [ecx+0x18], 0x0
mov al, [edx]
dec eax
cmp eax, 0x7
ja near loc_4083A2
jmp dword [eax*4+loc_4083AC]
loc_4082ED:
mov dword [ecx], loc_408550
jmp short loc_408332
loc_4082F5:
mov dword [ecx], loc_4083E0
jmp short loc_408332
loc_4082FD:
mov dword [ecx], loc_408430
jmp short loc_408332
loc_408305:
mov dword [ecx], loc_408460
jmp short loc_408332
loc_40830D:
mov dword [ecx], loc_408490
jmp short loc_408332
loc_408315:
mov dword [ecx+0x18], 0x40000000
mov dword [ecx], loc_4085B0
jmp short loc_408332
loc_408324:
mov dword [ecx], loc_4084D0
jmp short loc_408332
loc_40832C:
mov dword [ecx], loc_408510
loc_408332:
xor eax, eax
mov dword [ecx+0x10], 0x0
mov ax, [edx+0x2]
mov [esp], eax
fild dword [esp]
fdivr dword [loc_4189D8]
fstp dword [ecx+0x14]
mov ax, [edx+0x4]
mov [ecx+0x4], ax
and eax, 0xffff
mov edx, eax
mov eax, 0x66666667
imul edx
sar edx, 0x2
mov eax, edx
shr eax, 0x1f
add edx, eax
test dx, dx
mov [ecx+0x6], dx
jz short loc_408399
xor edx, edx
mov dword [ecx+0x8], 0x0
mov dx, [ecx+0x6]
mov [esp], edx
fild dword [esp]
fdivr dword [loc_4189F4]
fstp dword [ecx+0xc]
pop ecx
ret
loc_408399:
mov dword [ecx+0x8], 0x3f800000
pop ecx
ret
loc_4083A2:
mov dword [ecx], loc_4083D0
pop ecx
ret
align 4
loc_4083AC:
dd loc_4082ED
dd loc_4082F5
dd loc_4082FD
dd loc_408305
dd loc_40830D
dd loc_408315
dd loc_408324
dd loc_40832C
align 4
align 16
loc_4083D0:
fld dword [loc_4181E8]
ret
align 16
loc_4083E0:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_4083FB
fsub dword [loc_4189D8]
loc_4083FB:
fst dword [ecx+0x18]
fadd st0, st0
fcom dword [loc_4189F4]
fnstsw ax
test ah, 0x41
jnz short loc_408427
fcom dword [loc_418A18]
fnstsw ax
test ah, 0x41
jz short loc_408421
fsubr dword [loc_4189D8]
ret
loc_408421:
fsub dword [loc_418A08]
loc_408427:
ret
align 16
loc_408430:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_40844B
fsub dword [loc_4189D8]
loc_40844B:
fst dword [ecx+0x18]
fsub dword [loc_4189F4]
ret
align 16
loc_408460:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_40847B
fsub dword [loc_4189D8]
loc_40847B:
fst dword [ecx+0x18]
fsubr dword [loc_4189F4]
ret
align 16
loc_408490:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_4084AB
fsub dword [loc_4189D8]
loc_4084AB:
fst dword [ecx+0x18]
fcomp dword [loc_4189F4]
fnstsw ax
test ah, 0x41
jnz short loc_4084C2
fld dword [loc_418A10]
ret
loc_4084C2:
fld dword [loc_4189F4]
ret
align 16
loc_4084D0:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_4084F3
fstp st0
fld dword [loc_4189D8]
mov dword [ecx], loc_4083D0
loc_4084F3:
fst dword [ecx+0x18]
fmul dword [loc_4189D4]
fsub dword [loc_4189F4]
ret
align 16
loc_408510:
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_408533
fstp st0
fld dword [loc_4189D8]
mov dword [ecx], loc_4083D0
loc_408533:
fst dword [ecx+0x18]
fmul dword [loc_4189D4]
fsubr dword [loc_4189F4]
ret
align 16
loc_408550:
push ebp
mov ebp, esp
sub esp, 0x8
fld dword [ecx+0x14]
fadd dword [ecx+0x18]
fld st0
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_408571
fsub dword [loc_4189D8]
loc_408571:
fst dword [ecx+0x18]
fmul dword [loc_418A1C]
fstp dword [ebp-0x8]
fld dword [ebp-0x8]
fistp dword [ebp-0x4]
mov eax, [ebp-0x4]
fld dword [eax*4+loc_440E88]
fld dword [eax*4+loc_440E8C]
fsub st0, st1
fild dword [ebp-0x4]
fsubr dword [ebp-0x8]
fmulp st1, st0
faddp st1, st0
mov esp, ebp
pop ebp
ret
align 16
loc_4085B0:
sub esp, 0x8
push esi
mov esi, ecx
fld dword [esi+0x14]
fadd dword [esi+0x18]
fst dword [esp+0x4]
fcomp dword [loc_4189D8]
fnstsw ax
test ah, 0x41
jnz short loc_408600
fld dword [esp+0x4]
fsub dword [loc_4189D8]
fstp dword [esp+0x4]
call rand_asm
mov [esp+0x8], eax
mov eax, [esp+0x4]
fild dword [esp+0x8]
mov [esi+0x18], eax
pop esi
fmul dword [loc_418A20]
fsub dword [loc_4189F4]
add esp, 0x8
ret
loc_408600:
mov eax, [esp+0x4]
fld dword [esp+0x8]
mov [esi+0x18], eax
pop esi
add esp, 0x8
ret
loc_408610:
push ebx
xor ebx, ebx
mov bl, [ecx+loc_4189AC]
cmp ebx, 0x6
jae short loc_408692
mov eax, [loc_41B6F0]
and eax, 0xff
cmp eax, ebx
jz short loc_40867E
mov eax, [loc_41B704]
mov [loc_41B6F0], bl
test eax, eax
jz short loc_408654
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_408654:
lea ecx, [ebx*8]
sub ecx, ebx
add ecx, loc_418980
mov edx, [ecx]
mov [loc_455D60], edx
mov ax, [ecx+0x4]
mov [loc_455D64], ax
mov cl, [ecx+0x6]
mov [loc_455D66], cl
loc_40867E:
lea edx, [ebx*8]
sub edx, ebx
mov al, [edx+loc_418981]
mov [loc_455D61], al
loc_408692:
pop ebx
ret
align 16
loc_4086A0:
mov al, [loc_455D62]
push ebx
mov bl, cl
cmp al, bl
jz short loc_4086DB
mov eax, [loc_41B704]
test eax, eax
jz short loc_4086CE
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_4086CE:
mov [loc_455D62], bl
mov byte [loc_455D60], 0x1
loc_4086DB:
pop ebx
ret
align 16
loc_4086E0:
mov al, [loc_455D63]
push ebx
mov bl, cl
cmp al, bl
jz short loc_40871B
mov eax, [loc_41B704]
test eax, eax
jz short loc_40870E
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_40870E:
mov [loc_455D63], bl
mov byte [loc_455D60], 0x1
loc_40871B:
pop ebx
ret
align 16
loc_408720:
mov al, [loc_455D64]
push ebx
mov bl, cl
cmp al, bl
jz short loc_40875B
mov eax, [loc_41B704]
test eax, eax
jz short loc_40874E
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_40874E:
mov [loc_455D64], bl
mov byte [loc_455D60], 0x1
loc_40875B:
pop ebx
ret
align 16
loc_408760:
mov al, [loc_455D65]
push ebx
mov bl, cl
cmp al, bl
jz short loc_40879B
mov eax, [loc_41B704]
test eax, eax
jz short loc_40878E
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_40878E:
mov [loc_455D65], bl
mov byte [loc_455D60], 0x1
loc_40879B:
pop ebx
ret
align 16
loc_4087A0:
mov eax, [loc_41B704]
test eax, eax
jz short loc_4087C2
mov edx, 0x1000
mov ecx, loc_441850
call loc_40DA90
mov dword [loc_41B704], 0x0
loc_4087C2:
ret
align 16
loc_4087D0:
fld dword [loc_455D24]
fmul dword [esp+0x4]
mov eax, [esp+0x4]
mov [loc_41B6E4], eax
fcom dword [loc_418A24]
fnstsw ax
test ah, 0x41
jnz short loc_4087F8
fstp st0
fld dword [loc_418A24]
loc_4087F8:
fld dword [loc_455D1C]
fmul st0, st1
fstp dword [loc_4558C4]
fstp st0
fld dword [loc_455D30]
fmul dword [esp+0x4]
fcom dword [loc_418A24]
fnstsw ax
test ah, 0x41
jnz short loc_408827
fstp st0
fld dword [loc_418A24]
loc_408827:
fld dword [loc_455D28]
fmul st0, st1
fstp dword [loc_4558B0]
fstp st0
ret 0x4
align 16
loc_408840:
push ebx
mov ebx, ecx
cmp ebx, 0x6
jae near loc_40894B
mov eax, [loc_41B6E8]
and eax, 0xff
cmp eax, ebx
jz short loc_4088A8
mov eax, [loc_41B700]
mov [loc_41B6E8], bl
test eax, eax
jz short loc_408882
mov edx, 0x4000
mov ecx, loc_445888
call loc_40DA90
mov dword [loc_41B700], 0x0
loc_408882:
lea ecx, [ebx+ebx*8]
push esi
push edi
mov edi, loc_455D18
lea esi, [ecx*8+loc_4187B8]
mov ecx, 0x12
rep movsd
pop edi
pop esi
mov dword [loc_41B6EC], 0x0
pop ebx
ret
loc_4088A8:
mov eax, [loc_41B6EC]
test eax, eax
jz near loc_408941
fld dword [loc_41B6E4]
lea eax, [ebx+ebx*8]
shl eax, 0x3
mov edx, [eax+loc_4187C4]
mov ecx, [eax+loc_4187D0]
mov [loc_455D24], edx
mov edx, [eax+loc_4187D4]
fmul dword [loc_455D24]
mov [loc_455D30], ecx
mov [loc_455D34], edx
fcom dword [loc_418A24]
fnstsw ax
test ah, 0x41
jnz short loc_408900
fstp st0
fld dword [loc_418A24]
loc_408900:
fld dword [loc_455D1C]
fmul st0, st1
fstp dword [loc_4558C4]
fstp st0
fld dword [loc_41B6E4]
fmul dword [loc_455D30]
fcom dword [loc_418A24]
fnstsw ax
test ah, 0x41
jnz short loc_408931
fstp st0
fld dword [loc_418A24]
loc_408931:
fld dword [loc_455D28]
fmul st0, st1
fstp dword [loc_4558B0]
fstp st0
loc_408941:
mov dword [loc_41B6EC], 0x0
loc_40894B:
pop ebx
ret
align 16
loc_408950:
push ecx
and ecx, 0xff
mov dword [loc_41B6EC], 0x1
mov [esp], ecx
fild dword [esp]
fmul dword [loc_418A28]
fstp dword [loc_455D34]
pop ecx
ret
align 16
loc_408980:
push ecx
mov eax, [loc_41B6E8]
mov dword [loc_41B6EC], 0x1
and eax, 0xff
and ecx, 0xff
mov [esp], ecx
fild dword [esp]
fmul dword [eax*4+loc_418968]
fmul dword [loc_418A28]
fst dword [loc_455D30]
fstp dword [loc_455D24]
pop ecx
ret
align 16
loc_4089C0:
mov eax, [loc_41B6F4]
test eax, eax
jz short loc_4089F2
mov dword [loc_44102C], loc_40BB60
mov dword [loc_441030], loc_40BD10
mov dword [loc_441034], loc_40BF20
mov dword [loc_441038], loc_40C130
ret
loc_4089F2:
mov dword [loc_44102C], loc_40C950
mov dword [loc_441030], loc_40CAE0
mov dword [loc_441034], loc_40CCC0
mov dword [loc_441038], loc_40CEA0
ret
align 16
loc_408A20:
fld dword [loc_41B6E4]
fmul dword [loc_455D24]
mov eax, [loc_455D20]
mov ecx, [loc_455D2C]
mov [loc_4558C8], eax
mov dword [loc_455D18], 0x0
fcom dword [loc_418A24]
mov dword [loc_455888], loc_445888
mov dword [loc_4558A8], 0x0
mov dword [loc_4558A4], 0x0
mov dword [loc_455900], 0x0
mov dword [loc_4558FC], 0x0
mov [loc_4558AC], ecx
fnstsw ax
test ah, 0x41
jnz short loc_408A93
fstp st0
fld dword [loc_418A24]
loc_408A93:
fld dword [loc_455D1C]
fmul st0, st1
fstp dword [loc_4558C4]
fstp st0
fld dword [loc_455D30]
fmul dword [loc_41B6E4]
fcom dword [loc_418A24]
fnstsw ax
test ah, 0x41
jnz short loc_408AC4
fstp st0
fld dword [loc_418A24]
loc_408AC4:
mov eax, [loc_455D38]
xor ecx, ecx
mov cx, [loc_455D3A]
and eax, 0xffff
mov edx, eax
add eax, ecx
mov ecx, [loc_455D3C]
neg edx
mov [loc_45588C], edx
mov edx, eax
and ecx, 0xffff
neg edx
add eax, ecx
mov [loc_455890], edx
xor ecx, ecx
mov edx, eax
mov cx, [loc_455D3E]
neg edx
add eax, ecx
mov [loc_455894], edx
mov edx, eax
or ecx, 0xffffffff
neg edx
mov [loc_455898], edx
mov edx, [loc_44184C]
sub ecx, edx
mov edx, ecx
sub edx, eax
mov eax, [loc_455D50]
and eax, 0xffff
mov [loc_45589C], edx
neg eax
xor edx, edx
mov [loc_4558DC], eax
mov dx, [loc_455D52]
mov eax, [loc_455D54]
neg edx
and eax, 0xffff
mov [loc_4558EC], edx
neg eax
xor edx, edx
mov [loc_4558E0], eax
mov dx, [loc_455D56]
mov eax, [loc_455D40]
neg edx
and eax, 0xffff
mov [loc_4558F0], edx
mov edx, eax
neg edx
mov [loc_4558B8], edx
mov edx, [loc_455D48]
and edx, 0xffff
add eax, edx
mov edx, eax
neg edx
mov [loc_4558BC], edx
xor edx, edx
mov dx, [loc_455D42]
add eax, edx
fld dword [loc_455D28]
mov edx, eax
neg edx
mov [loc_4558C0], edx
xor edx, edx
mov dx, [loc_455D4A]
add eax, edx
fmul st0, st1
mov edx, eax
sub ecx, eax
mov eax, [loc_455D58]
mov [loc_4558A0], ecx
and eax, 0xffff
xor ecx, ecx
fstp dword [loc_4558B0]
mov cx, [loc_455D5A]
neg edx
neg eax
fstp st0
mov [loc_4558CC], edx
mov [loc_4558E4], eax
neg ecx
mov edx, [loc_455D5C]
xor eax, eax
mov ax, [loc_455D5E]
and edx, 0xffff
neg eax
neg edx
mov [loc_4558F8], eax
mov eax, [loc_455D44]
mov [loc_4558E8], edx
mov edx, [loc_455D4C]
and eax, 0xffff
mov [loc_4558F4], ecx
and edx, 0xffff
mov ecx, eax
add eax, edx
xor edx, edx
mov dx, [loc_455D46]
neg ecx
mov [loc_4558D0], ecx
mov ecx, eax
add eax, edx
xor edx, edx
mov dx, [loc_455D4E]
neg ecx
mov [loc_4558D4], ecx
mov ecx, eax
add edx, eax
neg ecx
neg edx
mov [loc_4558D8], ecx
mov [loc_4558B4], edx
ret
align 16
loc_408C80:
mov eax, [loc_41B700]
test eax, eax
jz short loc_408CA2
mov edx, 0x4000
mov ecx, loc_445888
call loc_40DA90
mov dword [loc_41B700], 0x0
loc_408CA2:
ret
align 16
loc_408CB0:
sub esp, 0x2c
push ebx
mov ebx, edx
push ebp
push esi
mov esi, [ebx+0x14]
mov ebp, ecx
xor eax, eax
push edi
movsx ecx, byte [esi+0x1d]
mov al, [ebx+0x2c]
mov dl, [esi+0x35]
mov [esp+0x10], ecx
mov cl, [esi+0x3f]
mov edi, [eax*4+loc_455D68]
mov eax, [ebp+0x20]
mov [esp+0x2c], cl
mov [esp+0x30], ebx
mov ecx, [eax]
mov [esp+0x14], ebp
test ecx, ecx
mov [esp+0x24], dl
jz short loc_408D28
mov edx, [esp+0x44]
and edx, 0xff
add eax, edx
mov edx, [esp+0x10]
movsx ecx, byte [eax+0x4]
add edx, ecx
mov cl, [eax+0x84]
cmp cl, 0xff
mov [esp+0x10], edx
jz short loc_408D1A
mov [esp+0x24], cl
loc_408D1A:
mov al, [eax+0x184]
cmp al, 0xff
jz short loc_408D28
mov [esp+0x2c], al
loc_408D28:
mov edx, [esp+0x48]
mov ecx, [esp+0x40]
mov eax, [esp+0x44]
mov [ebx+0x10], edi
mov dword [edi+0x20], 0x0
mov dword [edi], 0x0
mov ecx, [ecx]
push edx
push eax
mov edx, edi
call loc_409730
mov edx, [esp+0x40]
mov ecx, [edx+0x4]
test ecx, ecx
jz short loc_408D6C
mov eax, [esp+0x48]
mov edx, [esp+0x44]
push eax
push edx
lea edx, [edi+0x20]
call loc_409730
loc_408D6C:
fild dword [esp+0x10]
movsx eax, byte [esi+0x1e]
fmul dword [loc_4181EC]
mov [esp+0x28], eax
fiadd dword [esp+0x28]
fst dword [ebx+0x1c]
fld dword [ebp+0x28]
fmul dword [ebp+0x24]
fadd dword [ebp+0x30]
fadd dword [ebp+0x2c]
fadd st0, st1
fadd dword [loc_42BA08]
fstp dword [edi+0x40]
movsx ecx, byte [esi+0x1f]
fstp st0
mov [esp+0x28], ecx
fild dword [esp+0x28]
fmul dword [loc_41965C]
fstp dword [edi+0x48]
mov al, [esi+0x20]
test al, al
jl short loc_408DD1
movsx edx, al
xor eax, eax
mov ax, [edx*2+loc_418A2C]
mov [esp+0x28], eax
fild dword [esp+0x28]
jmp short loc_408DF0
loc_408DD1:
movsx ecx, al
shl ecx, 1
mov edx, loc_418A2C
sub edx, ecx
xor eax, eax
mov ax, [edx]
mov [esp+0x28], eax
fild dword [esp+0x28]
fmul dword [loc_418A10]
loc_408DF0:
fcom dword [loc_4181E8]
fst dword [ebx+0x24]
fnstsw ax
test ah, 0x1
jnz short loc_408E12
fld dword [ebp+0x48]
fadd dword [ebp+0x44]
mov ecx, [ebx+0x10]
fadd st0, st1
fstp dword [ecx+0x44]
fstp st0
jmp short loc_408E1E
loc_408E12:
fsub dword [ebp+0x44]
mov edx, [ebx+0x10]
fsub dword [ebp+0x48]
fstp dword [edx+0x44]
loc_408E1E:
xor eax, eax
mov al, [esi+0x24]
dec eax
jz short loc_408E67
dec eax
jz short loc_408E50
dec eax
jz short loc_408E30
xor eax, eax
jmp short loc_408E70
loc_408E30:
mov eax, [esp+0x48]
and eax, 0xff
imul eax, eax
cdq
and edx, 0x7f
add eax, edx
mov ecx, eax
mov eax, 0x7f
sar ecx, 0x7
sub eax, ecx
jmp short loc_408E70
loc_408E50:
mov eax, [esp+0x48]
and eax, 0xff
imul eax, eax
cdq
and edx, 0x7f
add eax, edx
sar eax, 0x7
jmp short loc_408E70
loc_408E67:
mov eax, [esp+0x48]
and eax, 0xff
loc_408E70:
mov cl, [esi+0x25]
test cl, cl
jl short loc_408E91
movsx edx, cl
mov [esp+0x28], edx
fild dword [esp+0x28]
fmul dword [eax*4+loc_4191AC]
fmul dword [loc_419658]
jmp short loc_408EAE
loc_408E91:
shl eax, 0x2
mov edx, loc_4193AC
sub edx, eax
movsx eax, cl
mov [esp+0x28], eax
fild dword [esp+0x28]
fmul dword [edx]
fmul dword [loc_419654]
loc_408EAE:
fadd dword [loc_4189F4]
mov ecx, [ebx+0x14]
fst dword [ebx+0x28]
movsx eax, byte [ebp+0x56]
movsx edx, byte [ecx+0x22]
add eax, edx
jns short loc_408ECA
xor eax, eax
jmp short loc_408ED4
loc_408ECA:
cmp eax, 0x7f
jle short loc_408ED4
mov eax, 0x7f
loc_408ED4:
fmul dword [eax*4+loc_4193AC]
xor edx, edx
fstp dword [edi+0x70]
movsx eax, byte [esi+0x2c]
mov [esp+0x28], eax
mov eax, [esp+0x44]
fild dword [esp+0x28]
and eax, 0xff
mov [esp+0x18], eax
fmul dword [loc_419650]
fstp dword [edi+0x64]
movsx ecx, byte [esi+0x28]
mov [esp+0x28], ecx
mov ecx, eax
fild dword [esp+0x28]
fmul dword [loc_41964C]
fstp dword [edi+0x68]
mov dl, [esi+0x29]
sub ecx, edx
movsx edx, byte [esi+0x2b]
mov [esp+0x44], ecx
mov ecx, [esp+0x48]
fild dword [esp+0x44]
mov [esp+0x44], edx
and ecx, 0xff
xor edx, edx
fimul dword [esp+0x44]
mov [esp+0x44], ecx
add ecx, 0xffffffc0
mov [esp+0x48], ecx
fmul dword [loc_419648]
fstp dword [edi+0x74]
fild dword [esp+0x48]
movsx ecx, byte [esi+0x26]
fstp dword [esp+0x28]
mov [esp+0x48], ecx
mov dl, [esi+0x29]
fild dword [esp+0x48]
sub eax, edx
mov [esp+0x48], eax
fmul dword [esp+0x28]
movsx eax, byte [esi+0x2a]
fmul dword [loc_419644]
fsubr dword [loc_4189F4]
fst dword [esp+0x10]
fild dword [esp+0x48]
mov [esp+0x48], eax
fimul dword [esp+0x48]
fmul dword [loc_419640]
fadd dword [loc_41963C]
fcom dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_408FB4
fstp st0
fld dword [loc_4181E8]
loc_408FB4:
fld st0
call _ftol_asm
mov [esp+0x48], eax
cmp eax, 0x7f
fisub dword [esp+0x48]
jle short loc_408FCD
mov eax, 0x7f
loc_408FCD:
fld dword [eax*4+loc_418DAC]
inc eax
cmp eax, 0x7f
jle short loc_408FDF
mov eax, 0x7f
loc_408FDF:
fld dword [eax*4+loc_418DAC]
fsub st0, st1
lea eax, [edi+0x4c]
lea ecx, [esi+0x2d]
mov [esp+0x1c], eax
lea ebp, [edi+0x5c]
fmul st0, st2
lea ebx, [esi+0x31]
mov [esp+0x20], ecx
fadd st0, st1
fstp dword [esp+0x48]
fstp st0
fstp st0
fld dword [esp+0x10]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_409021
fstp st0
fld dword [loc_4181E8]
loc_409021:
fld dword [esp+0x48]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_40903A
mov dword [esp+0x48], 0x0
loc_40903A:
mov dword [esp+0x10], 0x4
loc_409042:
mov dl, [ebx]
xor ecx, ecx
mov [esp+0x34], dl
inc ebx
mov eax, [esp+0x34]
and eax, 0xff
mov cx, [eax*2+loc_418CAC]
mov [esp+0x38], ecx
fild dword [esp+0x38]
fmul st0, st1
fmul dword [esp+0x48]
call _ftol_asm
and eax, 0xffff
add ebp, 0x2
mov ecx, eax
fstp st0
lea eax, [ecx+ecx*2]
shl eax, 0x4
add eax, ecx
fld dword [loc_4189F4]
lea eax, [eax+eax*4]
lea edx, [eax+eax*8]
mov eax, 0x51eb851f
lea ecx, [edx+edx+0x3200]
mul ecx
mov ecx, [esp+0x20]
mov eax, [esp+0x1c]
shr edx, 0xd
mov [ebp-0x2], dx
xor edx, edx
mov dl, [ecx]
add eax, 0x4
mov [esp+0x38], edx
mov [esp+0x1c], eax
fild dword [esp+0x38]
inc ecx
mov [esp+0x20], ecx
fmul dword [loc_4181E0]
fstp dword [eax-0x4]
mov eax, [esp+0x10]
dec eax
mov [esp+0x10], eax
jnz near loc_409042
mov al, [esi+0x27]
test al, al
fstp st0
jl short loc_40910B
mov edx, [esp+0x44]
mov ecx, 0x7f
sub ecx, edx
mov [esp+0x48], ecx
fild dword [esp+0x48]
movsx edx, al
mov [esp+0x48], edx
fimul dword [esp+0x48]
fmul dword [loc_419638]
jmp short loc_409120
loc_40910B:
movsx eax, al
mov [esp+0x48], eax
fild dword [esp+0x48]
fimul dword [esp+0x44]
fmul dword [loc_419634]
loc_409120:
fsubr dword [loc_4189F4]
lea eax, [edi+0x4c]
mov ecx, 0x4
loc_40912E:
fld st0
fmul dword [eax]
add eax, 0x4
dec ecx
fstp dword [eax-0x4]
jnz short loc_40912E
mov edx, [esp+0x14]
movsx ecx, byte [esi+0x23]
fstp st0
movsx eax, byte [edx+0x55]
add eax, ecx
jns short loc_409151
xor eax, eax
jmp short loc_40915B
loc_409151:
cmp eax, 0x7f
jle short loc_40915B
mov eax, 0x7f
loc_40915B:
mov eax, [eax*4+loc_418FAC]
mov [edi+0x6c], eax
xor eax, eax
mov al, [esi+0x21]
sub eax, 0x0
jz short loc_409190
dec eax
jz short loc_409187
dec eax
jz short loc_40917E
mov dword [edi+0x78], 0x0
jmp short loc_409197
loc_40917E:
mov dword [edi+0x78], 0x3
jmp short loc_409197
loc_409187:
mov dword [edi+0x78], 0x2
jmp short loc_409197
loc_409190:
mov dword [edi+0x78], 0x1
loc_409197:
mov eax, [esp+0x44]
xor ecx, ecx
mov cl, [eax+loc_4195AC]
mov al, [esi+0x3c]
mov [esp+0x48], ecx
fild dword [esp+0x48]
test al, al
fmul dword [loc_4181E0]
fsubr dword [loc_4189F4]
jl short loc_40921A
movsx ecx, al
mov [esp+0x48], ecx
fild dword [esp+0x48]
fmul dword [loc_419640]
fadd dword [loc_4189F4]
fmulp st1, st0
fcom dword [loc_4189F4]
fnstsw ax
test ah, 0x41
jnz short loc_4091EC
fstp st0
fld dword [loc_4189F4]
loc_4091EC:
xor eax, eax
mov al, [esi+0x3b]
dec eax
jz short loc_409261
dec eax
jz short loc_409208
dec eax
jz short loc_409204
fstp st0
fld dword [loc_4189F4]
jmp short loc_409267
loc_409204:
fld st0
jmp short loc_40925F
loc_409208:
fsubr dword [loc_4189F4]
fld st0
fmulp st1, st0
fsubr dword [loc_4189D8]
jmp short loc_409267
loc_40921A:
xor ecx, ecx
mov cl, [esi+0x3b]
dec ecx
jz short loc_409248
dec ecx
jz short loc_409238
dec ecx
jz short loc_409232
fstp st0
fld dword [loc_4181E8]
jmp short loc_409248
loc_409232:
fld st0
fmulp st1, st0
jmp short loc_409248
loc_409238:
fsubr dword [loc_4189F4]
fld st0
fmulp st1, st0
fsubr dword [loc_4189F4]
loc_409248:
movsx eax, al
mov [esp+0x48], eax
fild dword [esp+0x48]
fmul dword [loc_419640]
fadd dword [loc_4189F4]
loc_40925F:
fmulp st1, st0
loc_409261:
fsubr dword [loc_4189F4]
loc_409267:
mov ecx, [esp+0x24]
mov eax, [edx+0x18]
and ecx, 0xff
mov [esp+0x48], ecx
fild dword [esp+0x48]
test eax, eax
fmul st0, st1
fmulp st1, st0
fmul dword [loc_4181E0]
jz short loc_409299
xor ecx, ecx
mov cl, [eax+0x2]
mov [esp+0x48], ecx
fimul dword [esp+0x48]
jmp short loc_4092A9
loc_409299:
mov eax, [edx+0x1c]
xor ecx, ecx
mov cl, [eax+0x2]
mov [esp+0x48], ecx
fimul dword [esp+0x48]
loc_4092A9:
mov al, [esi+0x3a]
fmul dword [loc_4181E0]
movsx ecx, al
mov [esp+0x48], ecx
fild dword [esp+0x48]
test al, al
fmul dword [loc_419640]
fstp dword [esp+0x48]
jl short loc_409303
mov ebx, [esp+0x18]
xor eax, eax
mov al, [esi+0x38]
lea ecx, [eax-0x18]
cmp ebx, ecx
jg short loc_4092E7
fld dword [loc_4189F4]
fsub dword [esp+0x48]
jmp short loc_409345
loc_4092E7:
lea ecx, [eax+0x18]
cmp ebx, ecx
jge short loc_409347
sub eax, ebx
add eax, 0x18
mov [esp+0x44], eax
fild dword [esp+0x44]
fmul dword [loc_419630]
jmp short loc_40933B
loc_409303:
mov ebx, [esp+0x18]
xor eax, eax
mov al, [esi+0x38]
lea ecx, [eax+0x18]
cmp ebx, ecx
jl short loc_40931F
fld dword [esp+0x48]
fadd dword [loc_4189F4]
jmp short loc_409345
loc_40931F:
lea ecx, [eax-0x18]
cmp ebx, ecx
jle short loc_409347
mov ecx, ebx
sub ecx, eax
sub ecx, 0x18
mov [esp+0x44], ecx
fild dword [esp+0x44]
fmul dword [loc_41962C]
loc_40933B:
fmul dword [esp+0x48]
fsubr dword [loc_4189F4]
loc_409345:
fmulp st1, st0
loc_409347:
fmul dword [loc_41B718]
mov eax, [esp+0x30]
push 0x0
push eax
lea ecx, [edi+0x7c]
fld st0
fstp dword [eax+0x20]
fld dword [edx+0x38]
fmul dword [edx+0x34]
fmul st0, st1
fstp dword [edi+0x90]
fstp st0
call loc_409880
movsx edx, byte [esi+0x37]
mov [esp+0x48], edx
xor ecx, ecx
fild dword [esp+0x48]
fmul dword [loc_419640]
fstp dword [edi+0xac]
movsx eax, byte [esi+0x3d]
mov [esp+0x48], eax
mov cl, [esi+0x38]
fild dword [esp+0x48]
movsx edx, byte [esi+0x39]
fmul dword [esp+0x28]
sub ebx, ecx
mov [esp+0x48], ebx
fmul dword [loc_419644]
fsubr dword [loc_4189F4]
fst dword [esp+0x10]
fild dword [esp+0x48]
mov [esp+0x48], edx
fimul dword [esp+0x48]
fmul dword [loc_419640]
fadd dword [loc_41963C]
fcom dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_4093E5
fstp st0
fld dword [loc_4181E8]
loc_4093E5:
fld st0
call _ftol_asm
mov [esp+0x48], eax
cmp eax, 0x7f
fisub dword [esp+0x48]
jle short loc_4093FE
mov eax, 0x7f
loc_4093FE:
fld dword [eax*4+loc_418DAC]
inc eax
cmp eax, 0x7f
jle short loc_409410
mov eax, 0x7f
loc_409410:
fld dword [eax*4+loc_418DAC]
fsub st0, st1
lea eax, [edi+0x94]
lea ecx, [esi+0x41]
mov [esp+0x44], eax
lea ebx, [edi+0xa4]
fmul st0, st2
lea ebp, [esi+0x45]
mov [esp+0x28], ecx
fadd st0, st1
fstp dword [esp+0x48]
fstp st0
fstp st0
fld dword [esp+0x10]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_409458
fstp st0
fld dword [loc_4181E8]
loc_409458:
fld dword [esp+0x48]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_409471
mov dword [esp+0x48], 0x0
loc_409471:
mov dword [esp+0x24], 0x4
loc_409479:
mov dl, [ebp]
xor ecx, ecx
mov [esp+0x38], dl
inc ebp
mov eax, [esp+0x38]
and eax, 0xff
mov cx, [eax*2+loc_418CAC]
mov [esp+0x34], ecx
fild dword [esp+0x34]
fmul st0, st1
fmul dword [esp+0x48]
call _ftol_asm
and eax, 0xffff
add ebx, 0x2
mov ecx, eax
fstp st0
lea eax, [ecx+ecx*2]
shl eax, 0x4
add eax, ecx
fld dword [loc_4189F4]
lea eax, [eax+eax*4]
lea edx, [eax+eax*8]
mov eax, 0x51eb851f
lea ecx, [edx+edx+0x3200]
mul ecx
mov ecx, [esp+0x28]
mov eax, [esp+0x44]
shr edx, 0xd
mov [ebx-0x2], dx
xor edx, edx
mov dl, [ecx]
add eax, 0x4
mov [esp+0x34], edx
mov [esp+0x44], eax
fild dword [esp+0x34]
inc ecx
mov [esp+0x28], ecx
fmul dword [loc_4181E0]
fstp dword [eax-0x4]
mov eax, [esp+0x24]
dec eax
mov [esp+0x24], eax
jnz near loc_409479
mov eax, [loc_455D10]
xor ebx, ebx
cmp eax, ebx
fstp st0
jz short loc_40956A
mov eax, [esp+0x2c]
and eax, 0xff
mov [esp+0x48], eax
mov eax, [esp+0x14]
fild dword [esp+0x48]
fmul dword [eax+0x4c]
fmul dword [loc_41B70C]
fmul dword [loc_455D34]
fmul dword [loc_41B718]
fmul dword [loc_4181E0]
fst dword [edi+0xb0]
cmp [eax+0x1c], ebx
jz short loc_409576
fmul dword [loc_41B710]
fstp dword [edi+0xb0]
jmp short loc_409578
loc_40956A:
mov eax, [esp+0x14]
mov [edi+0xb0], ebx
jmp short loc_409578
loc_409576:
fstp st0
loc_409578:
cmp [loc_455D14], ebx
jz short loc_4095AC
xor ecx, ecx
mov cl, [esi+0x40]
mov [esp+0x48], ecx
fild dword [esp+0x48]
fmul dword [loc_4181E0]
fld dword [loc_44587C]
fmul dword [eax+0x50]
faddp st1, st0
fmul dword [loc_41B714]
fmul dword [loc_41B718]
jmp short loc_4095B2
loc_4095AC:
fld dword [loc_4181E8]
loc_4095B2:
fstp dword [edi+0xb4]
mov al, [esi+0x4a]
test al, al
jz near loc_4096CE
xor eax, eax
mov al, [esi+0x49]
cmp eax, 0x7
ja short loc_40961C
jmp dword [eax*4+loc_409710]
loc_4095D4:
mov byte [edi+0xb8], 0x1
jmp short loc_409623
loc_4095DD:
mov byte [edi+0xb8], 0x2
jmp short loc_409623
loc_4095E6:
mov byte [edi+0xb8], 0x3
jmp short loc_409623
loc_4095EF:
mov byte [edi+0xb8], 0x4
jmp short loc_409623
loc_4095F8:
mov byte [edi+0xb8], 0x5
jmp short loc_409623
loc_409601:
mov byte [edi+0xb8], 0x6
jmp short loc_409623
loc_40960A:
mov byte [edi+0xb8], 0x7
jmp short loc_409623
loc_409613:
mov byte [edi+0xb8], 0x8
jmp short loc_409623
loc_40961C:
mov byte [edi+0xb8], 0x0
loc_409623:
xor edx, edx
xor eax, eax
mov dl, [esi+0x4a]
mov ax, [edx*2+loc_418AAC]
lea ecx, [eax+eax*2]
shl ecx, 0x4
add ecx, eax
lea ecx, [ecx+ecx*4]
lea eax, [ecx+ecx*4]
lea eax, [eax+eax*8]
lea ecx, [eax*4+0x3200]
mov eax, 0x51eb851f
mul ecx
shr edx, 0xd
mov [edi+0xba], dx
mov edx, [esp+0x18]
movsx eax, byte [esi+0x4c]
add edx, 0xffffff3c
xor ecx, ecx
mov [esp+0x48], edx
mov cl, [esi+0x4b]
fild dword [esp+0x48]
mov [esp+0x48], eax
xor edx, edx
mov dx, [ecx*2+loc_418BAC]
fimul dword [esp+0x48]
mov [esp+0x48], edx
fmul dword [loc_419644]
fsubr dword [loc_4189F4]
fimul dword [esp+0x48]
call _ftol_asm
and eax, 0xffff
lea ecx, [eax+eax*2]
shl ecx, 0x4
add ecx, eax
lea ecx, [ecx+ecx*4]
lea eax, [ecx+ecx*8]
lea ecx, [eax+eax+0x3200]
mov eax, 0x51eb851f
mul ecx
shr edx, 0xd
mov [edi+0xbc], dx
jmp short loc_4096E5
loc_4096CE:
mov byte [edi+0xb8], 0x0
mov word [edi+0xba], 0x1
mov [edi+0xbc], bx
loc_4096E5:
mov edx, [esp+0x40]
pop edi
pop esi
pop ebp
mov eax, [edx+0x4]
cmp eax, ebx
pop ebx
jz short loc_40970A
mov eax, [esp+0x20]
mov ecx, [eax+0x8]
mov edx, [eax+0x1c]
mov [ecx+0x1c], edx
mov ecx, [eax+0x8]
mov edx, [eax+0x20]
mov [ecx+0x20], edx
loc_40970A:
add esp, 0x2c
ret 0xc
align 4
loc_409710:
dd loc_4095D4
dd loc_4095DD
dd loc_4095E6
dd loc_4095EF
dd loc_4095F8
dd loc_409601
dd loc_40960A
dd loc_409613
align 4
loc_409730:
mov eax, [ecx]
push ebx
push ebp
push esi
mov bl, [eax+0x8]
mov esi, edx
xor edx, edx
cmp bl, 0x1
setnz dl
inc edx
push edi
mov [esi], edx
mov edx, [eax+0x4]
mov [esi+0x4], edx
mov edx, [eax+0x14]
mov ebp, [eax+0x10]
mov edi, [esp+0x14]
sub edx, ebp
mov ebp, [esp+0x18]
mov [esi+0x8], edx
mov edx, [eax+0x14]
mov [esi+0xc], edx
mov bl, [eax+0xa]
xor edx, edx
cmp bl, 0x10
setnz dl
mov [esi+0x10], dx
xor edx, edx
mov dl, [eax+0x9]
and edi, 0xff
sub edi, edx
movsx edx, byte [ecx+0x4]
mov [esp+0x14], edi
fild dword [esp+0x14]
mov [esp+0x14], edx
movsx edx, byte [ecx+0x6]
fmul dword [loc_4181EC]
fild dword [esp+0x14]
mov [esp+0x14], edx
movsx edx, byte [ecx+0x5]
fmul dword [loc_419660]
fmulp st1, st0
fild dword [esp+0x14]
mov [esp+0x14], edx
fmul dword [loc_4189C8]
faddp st1, st0
fild dword [esp+0x14]
fmul dword [loc_4181EC]
faddp st1, st0
fstp dword [esi+0x14]
movsx edx, byte [eax+0xb]
mov [esp+0x14], edx
xor edx, edx
fild dword [esp+0x14]
fmul dword [loc_4189C8]
fstp dword [esi+0x18]
mov ax, [eax+0xc]
mov [esi+0x12], ax
mov dl, [ecx+0x7]
mov [esp+0x14], edx
mov dl, [ecx+0x9]
fild dword [esp+0x14]
test dl, dl
fmul dword [loc_4181E0]
jz short loc_40983D
xor eax, eax
and edx, 0xff
mov al, [ecx+0x8]
mov [esp+0x18], edx
mov edi, eax
mov eax, ebp
and eax, 0xff
add edx, edi
cmp edx, eax
jle short loc_40983D
sub eax, edi
pop edi
mov [esp+0x10], eax
fild dword [esp+0x10]
fidiv dword [esp+0x14]
fmulp st1, st0
fstp dword [esi+0x1c]
pop esi
pop ebp
pop ebx
ret 0x8
loc_40983D:
mov dl, [ecx+0xb]
test dl, dl
jz short loc_409872
xor eax, eax
and edx, 0xff
mov al, [ecx+0xa]
mov [esp+0x18], edx
mov ecx, eax
mov eax, ebp
and eax, 0xff
add edx, ecx
cmp edx, eax
jle short loc_409872
sub ecx, eax
mov [esp+0x14], ecx
fild dword [esp+0x14]
fidiv dword [esp+0x18]
fmulp st1, st0
loc_409872:
fstp dword [esi+0x1c]
pop edi
pop esi
pop ebp
pop ebx
ret 0x8
align 16
loc_409880:
sub esp, 0x8
xor eax, eax
push esi
mov esi, [edx+0x20]
push edi
mov edi, [esp+0x14]
mov al, [edi+0x18]
mov al, [eax+esi+0x104]
cmp al, 0xff
jz short loc_4098AF
movsx eax, al
mov [esp+0x14], eax
fild dword [esp+0x14]
fmul dword [loc_419640]
jmp short loc_4098C4
loc_4098AF:
mov eax, [edi+0x14]
movsx eax, byte [eax+0x36]
mov [esp+0x14], eax
fild dword [esp+0x14]
fmul dword [loc_419668]
loc_4098C4:
movsx edx, byte [edx+0x54]
mov [esp+0x14], edx
pop edi
fild dword [esp+0x10]
pop esi
fmul dword [loc_419640]
fadd st0, st1
fstp dword [esp+0xc]
fstp st0
fld dword [esp+0xc]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_40991C
fld dword [loc_4189F4]
fld dword [esp+0xc]
fadd dword [loc_4189F4]
fst dword [esp+0x4]
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_409945
mov dword [esp+0x4], 0x0
jmp short loc_409945
loc_40991C:
fld dword [loc_4189F4]
fsub dword [esp+0xc]
mov dword [esp+0x4], 0x3f800000
fld st0
fcomp dword [loc_4181E8]
fnstsw ax
test ah, 0x1
jz short loc_409945
fstp st0
fld dword [loc_4181E8]
loc_409945:
mov eax, [esp+0x10]
test eax, eax
jz short loc_409975
fsub dword [ecx+0xc]
mov dword [ecx], 0xa
fmul dword [loc_419664]
fstp dword [ecx+0x4]
fld dword [esp+0x4]
fsub dword [ecx+0x10]
fmul dword [loc_419664]
fstp dword [ecx+0x8]
add esp, 0x8
ret 0x8
loc_409975:
mov eax, [esp+0x4]
mov dword [ecx], 0x0
fstp dword [ecx+0xc]
mov [ecx+0x10], eax
add esp, 0x8
ret 0x8
align 16
loc_409990:
mov eax, [edx+0x14]
movsx ecx, byte [ecx+0x56]
movsx eax, byte [eax+0x22]
add eax, ecx
jns short loc_4099AC
xor eax, eax
fld dword [eax*4+loc_4193AC]
fmul dword [edx+0x28]
ret
loc_4099AC:
cmp eax, 0x7f
jle short loc_4099B6
mov eax, 0x7f
loc_4099B6:
fld dword [eax*4+loc_4193AC]
fmul dword [edx+0x28]
ret
InitializeDataFile_asm:
_InitializeDataFile_asm:
loc_409C20:
mov eax, [loc_455FEC]
test eax, eax
jnz short loc_409C2E
jmp loc_4056C0
loc_409C2E:
xor eax, eax
ret
InitializeSynth_asm:
_InitializeSynth_asm:
loc_409C50:
mov eax, [loc_455FEC]
mov [loc_41B72C], ecx
test eax, eax
mov [loc_41B730], edx
jnz short loc_409CA6
call loc_405990
mov ecx, [loc_41B730]
call loc_401000
mov eax, [loc_41B738]
mov ecx, [loc_41B734]
push eax
push ecx
mov ecx, [loc_41B72C]
mov edx, 0x1
call loc_407B20
mov eax, 0x1
mov dword [loc_41B728], 0xffffffff
mov [loc_455FEC], eax
loc_409CA6:
mov dword [loc_455D10], 0x1
mov dword [loc_455D14], 0x1
ret 0x4
MidiMessageShort_asm:
_MidiMessageShort_asm:
loc_409CE0:
mov eax, [loc_455FEC]
sub esp, 0x8
test eax, eax
jz near loc_40A110
mov eax, [loc_41B728]
inc eax
mov [loc_41B728], eax
jnz near loc_40A10A
and ecx, 0x7f7fff
push ebx
mov [esp+0x4], ecx
and ecx, 0xff
mov eax, ecx
and ecx, 0xf0
add ecx, 0xffffff80
and eax, 0xf
cmp ecx, 0x60
push esi
ja near loc_40A0F4
mov edx, [esp+0x9]
xor ebx, ebx
mov bl, [ecx+loc_40A134]
jmp dword [ebx*4+loc_40A118]
loc_409D3D:
test dh, dh
jz short loc_409D64
mov ecx, [esp+0xa]
lea eax, [eax+eax*2]
push ecx
mov dword [loc_455FF0], 0x1
mov ecx, [eax*4+loc_42B948]
call loc_401080
jmp loc_40A0F4
loc_409D64:
lea ecx, [eax+eax*2]
mov dword [loc_455FF0], 0x1
mov ecx, [ecx*4+loc_42B948]
call loc_401440
jmp loc_40A0F4
loc_409D82:
mov edx, [esp+0x9]
lea esi, [eax+eax*2]
mov eax, edx
and eax, 0xff
cmp eax, 0x7f
ja near loc_40A0F4
xor ecx, ecx
mov cl, [eax+loc_40A1E0]
jmp dword [ecx*4+loc_40A198]
loc_409DA8:
mov ecx, [esi*4+loc_42B948]
mov dl, dh
call loc_406020
jmp loc_40A0F4
loc_409DBB:
mov ecx, [esi*4+loc_42B948]
mov dl, dh
call loc_4060C0
jmp loc_40A0F4
loc_409DCE:
mov ecx, [esi*4+loc_42B948]
mov dl, dh
call loc_406130
jmp loc_40A0F4
loc_409DE1:
mov ecx, [esi*4+loc_42B948]
mov eax, [ecx+0x1c]
test eax, eax
jnz near loc_40A0F4
mov dl, dh
call loc_401590
jmp loc_40A0F4
loc_409DFF:
mov ecx, [esi*4+loc_42B948]
mov dl, dh
call loc_4061D0
jmp loc_40A0F4
loc_409E12:
mov edx, [esp+0xa]
mov eax, [esi*4+loc_42B948]
and edx, 0xff
mov [esp+0x8], edx
fild dword [esp+0x8]
fmul dword [loc_4189B8]
fstp dword [eax+0x4c]
jmp loc_40A0F4
loc_409E39:
mov ecx, [esp+0xa]
mov edx, [esi*4+loc_42B948]
and ecx, 0xff
mov [esp+0x8], ecx
fild dword [esp+0x8]
fmul dword [loc_4181E0]
fstp dword [edx+0x50]
jmp loc_40A0F4
loc_409E60:
mov ecx, [esi*4+loc_42B948]
call loc_405DD0
jmp loc_40A0F4
loc_409E71:
mov ecx, [esi*4+loc_42B948]
call loc_4015F0
jmp loc_40A0F4
loc_409E82:
mov ecx, [esi*4+loc_42B948]
call loc_401680
jmp loc_40A0F4
loc_409E93:
mov eax, [esi*4+loc_42B948]
mov [eax+0x5d], dh
jmp loc_40A0F4
loc_409EA2:
mov word [esi*4+loc_42B94E], 0x3fff
lea eax, [esi*4+loc_42B94C]
loc_409EB3:
mov dl, dh
xor ecx, ecx
and dl, 0x7f
mov ch, dl
mov dl, [eax]
and edx, 0x7f
or ecx, edx
mov [eax], cx
jmp loc_40A0F4
loc_409ECB:
mov dl, dh
lea eax, [esi*4+loc_42B94C]
and dl, 0x7f
xor cx, cx
mov cl, dl
mov dx, [eax]
and edx, 0x7f00
mov word [esi*4+loc_42B94E], 0x3fff
or ecx, edx
mov [eax], cx
jmp loc_40A0F4
loc_409EF9:
mov word [esi*4+loc_42B94C], 0x3fff
lea eax, [esi*4+loc_42B94E]
jmp short loc_409EB3
loc_409F0C:
mov dl, dh
lea eax, [esi*4+loc_42B94E]
and dl, 0x7f
xor cx, cx
mov cl, dl
mov dx, [eax]
and edx, 0x7f00
mov word [esi*4+loc_42B94C], 0x3fff
or ecx, edx
mov [eax], cx
jmp loc_40A0F4
loc_409F3A:
mov dl, dh
lea eax, [esi*4+loc_42B950]
and dl, 0x7f
xor cx, cx
mov cl, dl
mov dx, [eax]
and edx, 0x3f80
or ecx, edx
mov [eax], cx
jmp loc_40A0F4
loc_409F5E:
mov al, [esi*4+loc_42B950]
mov dl, dh
and dl, 0x7f
and eax, 0x7f
movzx dx, dl
shl edx, 0x7
or edx, eax
xor eax, eax
mov ax, [esi*4+loc_42B94E]
mov [esi*4+loc_42B950], dx
sub eax, 0x0
jz short loc_409FAF
dec eax
jz short loc_409FA1
dec eax
jnz short loc_409FBB
mov ecx, [esi*4+loc_42B948]
call loc_406360
jmp short loc_409FBB
loc_409FA1:
mov ecx, [esi*4+loc_42B948]
call loc_406420
jmp short loc_409FBB
loc_409FAF:
mov ecx, [esi*4+loc_42B948]
call loc_4062B0
loc_409FBB:
xor eax, eax
mov ax, [esi*4+loc_42B94C]
mov ecx, eax
sub ecx, 0x120
jz near loc_40A09C
dec ecx
jz near loc_40A086
and eax, 0xff00
cmp eax, 0x1c00
jg short loc_40A05D
jz short loc_40A03C
cmp eax, 0x1800
jz short loc_40A01B
cmp eax, 0x1a00
jnz near loc_40A0F4
mov cx, [esi*4+loc_42B950]
mov dl, [esi*4+loc_42B94C]
push ecx
mov ecx, [esi*4+loc_42B948]
call loc_4067F0
jmp loc_40A0F4
loc_40A01B:
mov dx, [esi*4+loc_42B950]
mov ecx, [esi*4+loc_42B948]
push edx
mov dl, [esi*4+loc_42B94C]
call loc_4067C0
jmp loc_40A0F4
loc_40A03C:
mov ax, [esi*4+loc_42B950]
mov dl, [esi*4+loc_42B94C]
mov ecx, [esi*4+loc_42B948]
push eax
call loc_406820
jmp loc_40A0F4
loc_40A05D:
cmp eax, 0x1d00
jnz near loc_40A0F4
mov cx, [esi*4+loc_42B950]
mov dl, [esi*4+loc_42B94C]
push ecx
mov ecx, [esi*4+loc_42B948]
call loc_406850
jmp short loc_40A0F4
loc_40A086:
mov dx, [esi*4+loc_42B950]
mov ecx, [esi*4+loc_42B948]
call loc_4068F0
jmp short loc_40A0F4
loc_40A09C:
mov dx, [esi*4+loc_42B950]
mov ecx, [esi*4+loc_42B948]
call loc_406880
jmp short loc_40A0F4
loc_40A0B2:
mov dl, [esp+0x9]
lea eax, [eax+eax*2]
mov ecx, [eax*4+loc_42B948]
call loc_4064E0
jmp short loc_40A0F4
loc_40A0C7:
mov ecx, [esp+0xa]
mov dl, [esp+0x9]
lea eax, [eax+eax*2]
push ecx
mov ecx, [eax*4+loc_42B948]
call loc_405D10
jmp short loc_40A0F4
loc_40A0E1:
mov dl, [esp+0x9]
lea ecx, [eax+eax*2]
mov ecx, [ecx*4+loc_42B948]
call loc_406930
loc_40A0F4:
mov eax, [loc_41B728]
pop esi
dec eax
pop ebx
mov [loc_41B728], eax
mov eax, 0x1
add esp, 0x8
ret
loc_40A10A:
dec dword [loc_41B728]
loc_40A110:
xor eax, eax
add esp, 0x8
ret
align 4
loc_40A118:
dd loc_409D64
dd loc_409D3D
dd loc_409D82
dd loc_40A0E1
dd loc_40A0B2
dd loc_40A0C7
dd loc_40A0F4
loc_40A134:
db 0
times 15 db 6
db 1
times 31 db 6
db 2
times 15 db 6
db 3
times 15 db 6
db 4
times 15 db 6
db 5
align 4
loc_40A198:
dd loc_409E93
dd loc_409DFF
dd loc_409F5E
dd loc_409DA8
dd loc_409DBB
dd loc_409DCE
dd loc_409F3A
dd loc_409DE1
dd loc_409E12
dd loc_409E39
dd loc_409ECB
dd loc_409EA2
dd loc_409F0C
dd loc_409EF9
dd loc_409E82
dd loc_409E60
dd loc_409E71
dd loc_40A0F4
loc_40A1E0:
db 0
db 1
times 4 db 17
db 2
db 3
db 17
db 17
db 4
db 5
times 26 db 17
db 6
times 25 db 17
db 7
times 26 db 17
db 8
db 17
db 9
times 4 db 17
db 10
db 11
db 12
db 13
times 18 db 17
db 14
db 15
db 17
db 16
times 4 db 14
align 4
MidiMessageLong_asm:
_MidiMessageLong_asm:
loc_40A260:
mov eax, [loc_455FEC]
test eax, eax
jz near loc_40A2F8
mov eax, [loc_41B728]
inc eax
mov [loc_41B728], eax
jnz short loc_40A2F2
mov al, [ecx]
push esi
cmp al, 0xf0
jnz short loc_40A2DE
cmp byte [ecx+edx-0x1], 0xf7
jnz short loc_40A2DE
xor eax, eax
mov al, [ecx+0x1]
lea esi, [eax-0x41]
cmp esi, 0x3e
ja short loc_40A2DE
xor eax, eax
mov al, [esi+loc_40A314]
jmp dword [eax*4+loc_40A300]
loc_40A2A4:
push 0x0
add edx, 0xfffffffe
add ecx, 0x2
call loc_404760
jmp short loc_40A2DE
loc_40A2B3:
push 0x0
add edx, 0xfffffffe
add ecx, 0x2
call loc_404790
jmp short loc_40A2DE
loc_40A2C2:
push 0x0
add edx, 0xfffffffe
add ecx, 0x2
call loc_4047F0
jmp short loc_40A2DE
loc_40A2D1:
push 0x0
add edx, 0xfffffffe
add ecx, 0x2
call loc_404840
loc_40A2DE:
mov eax, [loc_41B728]
pop esi
dec eax
mov [loc_41B728], eax
mov eax, 0x1
ret 0x4
loc_40A2F2:
dec dword [loc_41B728]
loc_40A2F8:
xor eax, eax
ret 0x4
align 4
loc_40A300:
dd loc_40A2D1
dd loc_40A2C2
dd loc_40A2A4
dd loc_40A2B3
dd loc_40A2DE
loc_40A314:
db 0
db 4
db 1
times 58 db 4
db 2
db 3
align 4
align 16
RenderSamples_asm:
_RenderSamples_asm:
loc_40A360:
mov eax, [loc_455FEC]
test eax, eax
jz short loc_40A3AF
mov eax, [loc_41B728]
inc eax
mov [loc_41B728], eax
jnz short loc_40A3A9
mov edx, 0x400
call loc_406A60
mov eax, [loc_455FF0]
test eax, eax
jz short loc_40A398
mov dword [loc_455FF0], 0x0
call loc_4069B0
loc_40A398:
mov eax, [loc_41B728]
dec eax
mov [loc_41B728], eax
mov eax, 0x1
ret
loc_40A3A9:
dec dword [loc_41B728]
loc_40A3AF:
xor eax, eax
ret
align 16
InitializeMasterVolume_asm:
_InitializeMasterVolume_asm:
loc_40A3C0:
mov eax, [loc_455FEC]
sub esp, 0x8
test eax, eax
jz short loc_40A3FA
mov [esp], ecx
mov dword [esp+0x4], 0x0
fild qword [esp]
fmul dword [loc_4189F0]
fstp dword [loc_41B6BC]
fld dword [loc_41B6B8]
fmul dword [loc_41B6BC]
fstp dword [loc_41B6FC]
loc_40A3FA:
add esp, 0x8
ret
InitializeEffect_asm:
_InitializeEffect_asm:
loc_40A480:
mov eax, ecx
push esi
mov ecx, [loc_455FEC]
mov esi, edx
test ecx, ecx
jz short loc_40A4C9
sub eax, 0x0
jz short loc_40A4B1
dec eax
jnz short loc_40A4C9
test esi, esi
jz short loc_40A4A9
mov eax, [loc_455D10]
test eax, eax
jnz short loc_40A4A9
call loc_408C80
loc_40A4A9:
mov [loc_455D10], esi
pop esi
ret
loc_40A4B1:
test esi, esi
jz short loc_40A4C3
mov eax, [loc_455D14]
test eax, eax
jnz short loc_40A4C3
call loc_4087A0
loc_40A4C3:
mov [loc_455D14], esi
loc_40A4C9:
pop esi
ret
align 16
InitializeUnknown_asm:
_InitializeUnknown_asm:
loc_40A4D0:
mov eax, [loc_455FEC]
test eax, eax
jz short loc_40A4DE
jmp loc_4089C0
loc_40A4DE:
ret
InitializeCpuLoad_asm:
_InitializeCpuLoad_asm:
loc_40A540:
sub esp, 0x8
xor eax, eax
push esi
mov esi, [loc_455FEC]
cmp esi, eax
pop esi
jz short loc_40A593
mov [esp], edx
mov [esp+0x4], eax
fild qword [esp]
mov [esp], ecx
mov [esp+0x4], eax
fmul dword [loc_4189F0]
fstp dword [loc_41B734]
fild qword [esp]
mov eax, [loc_41B734]
push eax
fmul dword [loc_4189F0]
fstp dword [loc_41B738]
mov ecx, [loc_41B738]
push ecx
call loc_407E60
loc_40A593:
add esp, 0x8
ret
align 16
InitializeParameters_asm:
_InitializeParameters_asm:
loc_40A5A0:
push ecx
mov eax, [loc_455FEC]
push esi
test eax, eax
mov esi, ecx
jz near loc_40A64F
xor eax, eax
xor ecx, ecx
mov ax, [esi+0x2]
xor edx, edx
mov [esp+0x4], eax
xor eax, eax
fild dword [esp+0x4]
fmul dword [loc_4189F0]
fstp dword [loc_41B70C]
mov cx, [esi+0x4]
mov [esp+0x4], ecx
push ecx
fild dword [esp+0x8]
fmul dword [loc_4189F0]
fstp dword [loc_41B710]
mov dx, [esi]
mov [esp+0x8], edx
fild dword [esp+0x8]
fmul dword [loc_4189F0]
fstp dword [loc_41B714]
mov ax, [esi+0x6]
mov [esp+0x8], eax
fild dword [esp+0x8]
fmul dword [loc_4189F0]
fstp dword [esp]
call loc_4087D0
xor ecx, ecx
xor edx, edx
mov cx, [esi+0x8]
mov [esp+0x4], ecx
fild dword [esp+0x4]
fmul dword [loc_4189F0]
fstp dword [loc_41B718]
mov dx, [esi+0xa]
mov [esp+0x4], edx
fild dword [esp+0x4]
fmul dword [loc_4189F0]
fstp dword [loc_41B6C0]
loc_40A64F:
pop esi
pop ecx
ret
align 16
loc_40A660:
jmp loc_4017E0
align 16
loc_40A670:
mov eax, [esp+0x4]
push eax
call loc_4018A0
ret 0x4
align 16
loc_40A680:
ret
ValidateSettings_asm:
_ValidateSettings_asm:
loc_40A8F0:
mov eax, [ecx]
cmp eax, 0x5622
jz short loc_40A907
cmp eax, 0xac44
jz short loc_40A907
mov eax, [loc_41B740]
mov [ecx], eax
loc_40A907:
mov eax, [ecx+0x4]
cmp eax, 0x8
jae short loc_40A918
mov dword [ecx+0x4], 0x8
jmp short loc_40A926
loc_40A918:
cmp eax, 0x100
jbe short loc_40A926
mov dword [ecx+0x4], 0x100
loc_40A926:
mov eax, [ecx+0x8]
cmp eax, 0x14
jae short loc_40A937
mov dword [ecx+0x8], 0x14
jmp short loc_40A943
loc_40A937:
cmp eax, 0x55
jbe short loc_40A943
mov dword [ecx+0x8], 0x55
loc_40A943:
mov eax, [ecx+0xc]
mov edx, 0x5a
cmp eax, edx
jb short loc_40A951
jbe short loc_40A954
loc_40A951:
mov [ecx+0xc], edx
loc_40A954:
mov eax, [ecx+0x10]
mov edx, 0x1
cmp eax, edx
jbe short loc_40A963
mov [ecx+0x10], edx
loc_40A963:
cmp [ecx+0x14], edx
jbe short loc_40A96B
mov [ecx+0x14], edx
loc_40A96B:
push edi
mov edi, [ecx+0x18]
mov eax, 0xc8
cmp edi, eax
jbe short loc_40A97B
mov [ecx+0x18], eax
loc_40A97B:
cmp [ecx+0x1c], eax
jbe short loc_40A983
mov [ecx+0x1c], eax
loc_40A983:
cmp [ecx+0x20], eax
jbe short loc_40A98B
mov [ecx+0x20], eax
loc_40A98B:
cmp [ecx+0x24], eax
jbe short loc_40A993
mov [ecx+0x24], eax
loc_40A993:
cmp [ecx+0x28], eax
jbe short loc_40A99B
mov [ecx+0x28], eax
loc_40A99B:
cmp [ecx+0x2c], eax
jbe short loc_40A9A3
mov [ecx+0x2c], eax
loc_40A9A3:
mov edi, [ecx+0x30]
mov eax, 0x64
cmp edi, eax
pop edi
jbe short loc_40A9B3
mov [ecx+0x30], eax
loc_40A9B3:
mov eax, [ecx+0x34]
cmp eax, edx
jae short loc_40A9BF
mov [ecx+0x34], edx
jmp short loc_40A9CB
loc_40A9BF:
cmp eax, 0x14
jbe short loc_40A9CB
mov dword [ecx+0x34], 0x14
loc_40A9CB:
mov eax, [ecx+0x38]
cmp eax, 0x28
jz short loc_40A9E1
cmp eax, 0x50
jz short loc_40A9E1
mov edx, [loc_41B778]
mov [ecx+0x38], edx
loc_40A9E1:
ret
loc_40AEB0:
push edx
fld dword [ecx+0x30]
fld dword [ecx+0x2c]
fld dword [ecx+0x3c]
fld dword [ecx+0x38]
fld dword [ecx+0x44]
fld dword [ecx+0x40]
mov eax, [loc_441848]
lea edx, [eax*4+loc_455904]
mov eax, loc_455904
jmp short loc_40AEE1
align 16
loc_40AEE1:
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st3
fld st2
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fadd st0, st1
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
cmp eax, edx
jb near loc_40AEE1
fstp dword [ecx+0x40]
fstp dword [ecx+0x44]
fstp st0
fstp st0
fstp st0
fstp st0
mov eax, [ecx+0x24]
mov [ecx+0x28], eax
pop edx
ret
align 16
loc_40B000:
push edx
fld dword [ecx+0x3c]
fld dword [ecx+0x38]
fld dword [ecx+0x34]
fld dword [ecx+0x2c]
fld dword [ecx+0x44]
fld dword [ecx+0x40]
mov eax, [loc_441848]
lea edx, [eax*4+loc_455904]
mov eax, loc_455904
jmp short loc_40B031
align 16
loc_40B031:
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
fld st0
fmul st0, st5
fld st2
fmul st0, st7
faddp st1, st0
fadd dword [eax]
fxch st0, st1
fxch st0, st2
fmul st0, st4
fld st1
fmul st0, st4
faddp st1, st0
fstp dword [eax]
lea eax, [eax+0x4]
cmp eax, edx
jb near loc_40B031
fstp dword [ecx+0x40]
fstp dword [ecx+0x44]
fstp st0
fstp st0
fstp st0
fstp st0
mov eax, [ecx+0x24]
mov [ecx+0x28], eax
pop edx
ret
align 16
loc_40B140:
push ebx
push edx
push eax
fld dword [ecx+0x44]
fld dword [ecx+0x40]
fld dword [ecx+0x24]
fsub dword [ecx+0x28]
fmul dword [loc_455D08]
fstp dword [esp]
mov eax, [loc_441848]
lea edx, [eax*4+loc_455904]
mov eax, loc_455904
jmp loc_40B207
align 16
loc_40B173:
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x4]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0x4]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x8]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0x8]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0xc]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0xc]
dec ebx
lea eax, [eax+0x10]
jnz near loc_40B173
cmp eax, edx
jae short loc_40B25B
fstp st0
fstp st0
fstp st0
fstp st0
loc_40B207:
mov ebx, [loc_455D0C]
shr ebx, 0x2
fld dword [ecx+0x28]
fadd dword [esp]
fst dword [ecx+0x28]
fld st0
fmul st1, st0
fmul dword [ecx+0x48]
fld dword [loc_419670]
fld dword [loc_419678]
fmul st3, st0
fadd st0, st2
fadd st0, st3
fdivp st1, st0
fld st2
fadd st0, st3
fld dword [loc_41967C]
fsub st0, st1
fmul st0, st2
fxch st0, st3
fsub st0, st4
fsub dword [loc_419678]
fmul st0, st2
fxch st0, st4
fmul st0, st2
fxch st0, st2
fmulp st1, st0
jmp loc_40B173
loc_40B25B:
xor eax, eax
mov [ecx+0xc], eax
fstp dword [ecx+0x30]
fstp dword [ecx+0x2c]
fstp dword [ecx+0x38]
fstp dword [ecx+0x3c]
fstp dword [ecx+0x40]
fstp dword [ecx+0x44]
pop eax
pop edx
pop ebx
ret
align 16
loc_40B280:
push ebx
push edx
push eax
fld dword [ecx+0x44]
fld dword [ecx+0x40]
fld dword [ecx+0x24]
fsub dword [ecx+0x28]
fmul dword [loc_455D08]
fstp dword [esp]
mov eax, [loc_441848]
lea edx, [eax*4+loc_455904]
mov eax, loc_455904
jmp loc_40B347
align 16
loc_40B2B3:
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x4]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0x4]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x8]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0x8]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0xc]
fld st5
fxch st0, st7
fadd st0, st1
fmul st0, st3
fxch st0, st1
fxch st0, st6
fmul st0, st2
faddp st1, st0
fstp dword [eax+0xc]
dec ebx
lea eax, [eax+0x10]
jnz near loc_40B2B3
cmp eax, edx
jae short loc_40B3A3
fstp st0
fstp st0
fstp st0
fstp st0
loc_40B347:
mov ebx, [loc_455D0C]
shr ebx, 0x2
fld dword [ecx+0x28]
fadd dword [esp]
fst dword [ecx+0x28]
fld st0
fmul st1, st0
fmul dword [ecx+0x48]
fld dword [loc_419670]
fld dword [loc_419678]
fmul st3, st0
fadd st0, st2
fadd st0, st3
fdivp st1, st0
fld dword [loc_41967C]
fsub st0, st3
fsub st0, st3
fmul st0, st1
fxch st0, st2
fsub st0, st3
fsub dword [loc_419678]
fmul st0, st1
fstp st3
fld st0
fmul dword [loc_419678]
fxch st0, st1
fmul dword [loc_419680]
jmp loc_40B2B3
loc_40B3A3:
xor eax, eax
mov [ecx+0xc], eax
fstp dword [ecx+0x30]
fstp dword [ecx+0x2c]
fstp dword [ecx+0x38]
fstp dword [ecx+0x3c]
fstp dword [ecx+0x40]
fstp dword [ecx+0x44]
pop eax
pop edx
pop ebx
ret
align 16
loc_40B3C0:
push ebx
push edx
push eax
fld dword [ecx+0x44]
fld dword [ecx+0x40]
fld dword [ecx+0x24]
fsub dword [ecx+0x28]
fmul dword [loc_455D08]
fstp dword [esp]
mov eax, [loc_441848]
lea edx, [eax*4+loc_455904]
mov eax, loc_455904
jmp loc_40B47B
align 16
loc_40B3F3:
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax]
fld st5
fxch st0, st7
fmul st0, st2
fxch st0, st1
fst st6
fmul st0, st3
faddp st1, st0
fstp dword [eax]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x4]
fld st5
fxch st0, st7
fmul st0, st2
fxch st0, st1
fst st6
fmul st0, st3
faddp st1, st0
fstp dword [eax+0x4]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0x8]
fld st5
fxch st0, st7
fmul st0, st2
fxch st0, st1
fst st6
fmul st0, st3
faddp st1, st0
fstp dword [eax+0x8]
fld st4
fmul st0, st3
fld st6
fmul st0, st5
faddp st1, st0
fadd dword [eax+0xc]
fld st5
fxch st0, st7
fmul st0, st2
fxch st0, st1
fst st6
fmul st0, st3
faddp st1, st0
fstp dword [eax+0xc]
dec ebx
lea eax, [eax+0x10]
jnz short loc_40B3F3
cmp eax, edx
jae short loc_40B4CF
fstp st0
fstp st0
fstp st0
fstp st0
loc_40B47B:
mov ebx, [loc_455D0C]
shr ebx, 0x2
fld dword [ecx+0x28]
fadd dword [esp]
fst dword [ecx+0x28]
fld st0
fmul st1, st0
fmul dword [ecx+0x48]
fld dword [loc_419670]
fld dword [loc_419678]
fmul st3, st0
fadd st0, st2
fadd st0, st3
fdivp st1, st0
fld dword [loc_41967C]
fsub st0, st3
fsub st0, st3
fmul st0, st1
fxch st0, st2
fld st0
fsub st0, st4
fsub dword [loc_419678]
fmul st0, st2
fstp st4
fmulp st1, st0
fld st0
fchs
jmp loc_40B3F3
loc_40B4CF:
xor eax, eax
mov [ecx+0xc], eax
fstp dword [ecx+0x34]
fstp dword [ecx+0x2c]
fstp dword [ecx+0x38]
fstp dword [ecx+0x3c]
fstp dword [ecx+0x40]
fstp dword [ecx+0x44]
pop eax
pop edx
pop ebx
ret
align 16
loc_40B4F0:
push ebx
push esi
push edi
push ecx
fld dword [loc_445880]
fld dword [loc_445878]
fld dword [loc_445874]
fld dword [loc_445870]
mov ecx, loc_441048
mov ebx, 0xfff
mov edx, [loc_44585C]
dec edx
sub edx, [loc_445860]
mov edi, loc_441850
mov eax, [loc_441848]
lea esi, [ecx+eax*4]
jmp short loc_40B548
align 16
loc_40B540:
cmp ecx, esi
jae near loc_40B5D1
loc_40B548:
fld st0
fabs
fist dword [esp]
mov eax, edx
sub eax, [esp]
and eax, ebx
lea eax, [edi+eax*4]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx]
fstp dword [ecx]
fld st3
fxch st0, st1
fsubp st1, st0
fist dword [esp]
mov eax, edx
sub eax, [esp]
and eax, ebx
lea eax, [edi+eax*4]
fild dword [esp]
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fld st0
fadd dword [ecx+0x400]
fstp dword [ecx+0x400]
fmul st0, st4
mov eax, [loc_445860]
inc edx
add eax, edx
lea eax, [edi+eax*4]
fadd dword [eax]
fstp dword [eax]
lea ecx, [ecx+0x4]
fadd st0, st1
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz near loc_40B540
fsub st0, st2
fsub st0, st2
cmp ecx, esi
jb near loc_40B548
loc_40B5D1:
fstp dword [loc_445870]
fstp st0
fstp st0
fstp st0
pop ecx
pop edi
pop esi
pop ebx
ret
align 16
loc_40B5F0:
push ebx
push esi
push edi
push ecx
fld dword [loc_445880]
fld dword [loc_445878]
fld dword [loc_445874]
fld dword [loc_445870]
mov ecx, loc_441048
mov ebx, [loc_445860]
mov edx, [loc_44585C]
dec edx
sub edx, ebx
mov edi, loc_441850
mov eax, [loc_441848]
lea esi, [ecx+eax*4]
jmp short loc_40B634
align 16
loc_40B630:
cmp ecx, esi
jae short loc_40B6AE
loc_40B634:
fld st0
fabs
fist dword [esp]
mov eax, edx
sub eax, [esp]
lea eax, [edi+eax*4]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx]
fstp dword [ecx]
fld st3
fxch st0, st1
fsubp st1, st0
fist dword [esp]
mov eax, edx
sub eax, [esp]
lea eax, [edi+eax*4]
fild dword [esp]
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fld st0
fadd dword [ecx+0x400]
fstp dword [ecx+0x400]
fmul st0, st4
inc edx
mov eax, ebx
add eax, edx
lea eax, [edi+eax*4]
fadd dword [eax]
fstp dword [eax]
lea ecx, [ecx+0x4]
fadd st0, st1
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40B630
fsub st0, st2
fsub st0, st2
cmp ecx, esi
jb short loc_40B634
loc_40B6AE:
fstp dword [loc_445870]
fstp st0
fstp st0
fstp st0
pop ecx
pop edi
pop esi
pop ebx
ret
align 16
loc_40B6C0:
push ebx
push esi
push edi
push ecx
fld dword [loc_445878]
fld dword [loc_445874]
fld dword [loc_445870]
mov ecx, loc_441048
mov ebx, 0xfff
mov edx, [loc_44585C]
dec edx
sub edx, [loc_445860]
mov edi, loc_441850
mov eax, [loc_441848]
lea esi, [ecx+eax*4]
jmp short loc_40B704
align 16
loc_40B700:
cmp ecx, esi
jae short loc_40B773
loc_40B704:
fld st0
fabs
fist dword [esp]
mov eax, edx
sub eax, [esp]
and eax, ebx
lea eax, [edi+eax*4]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx]
fstp dword [ecx]
fld st3
fxch st0, st1
fsubp st1, st0
fist dword [esp]
mov eax, edx
sub eax, [esp]
and eax, ebx
lea eax, [edi+eax*4]
fild dword [esp]
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx+0x400]
fstp dword [ecx+0x400]
inc edx
lea ecx, [ecx+0x4]
fadd st0, st1
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40B700
fsub st0, st2
fsub st0, st2
cmp ecx, esi
jb short loc_40B704
loc_40B773:
fstp dword [loc_445870]
fstp st0
fstp st0
pop ecx
pop edi
pop esi
pop ebx
ret
align 16
loc_40B790:
push ebx
push esi
push ecx
fld dword [loc_445878]
fld dword [loc_445874]
fld dword [loc_445870]
mov ecx, loc_441048
mov edx, [loc_44585C]
dec edx
sub edx, [loc_445860]
mov ebx, loc_441850
mov eax, [loc_441848]
lea esi, [ecx+eax*4]
jmp short loc_40B7D4
align 16
loc_40B7D0:
cmp ecx, esi
jae short loc_40B83F
loc_40B7D4:
fld st0
fabs
fist dword [esp]
mov eax, edx
sub eax, [esp]
lea eax, [ebx+eax*4]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx]
fstp dword [ecx]
fld st3
fxch st0, st1
fsubp st1, st0
fist dword [esp]
mov eax, edx
sub eax, [esp]
lea eax, [ebx+eax*4]
fild dword [esp]
fsubp st1, st0
fld dword [eax+0x4]
fld dword [eax]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fadd dword [ecx+0x400]
fstp dword [ecx+0x400]
inc edx
lea ecx, [ecx+0x4]
fadd st0, st1
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40B7D0
fsub st0, st2
fsub st0, st2
cmp ecx, esi
jb short loc_40B7D4
loc_40B83F:
fstp dword [loc_445870]
fstp st0
fstp st0
pop ecx
pop esi
pop ebx
ret
align 16
loc_40B850:
push ebx
push edx
push ebp
push esi
push edi
fld dword [loc_419690]
fld dword [loc_419694]
mov ebx, ecx
mov edx, ecx
mov ebp, ecx
add ebx, [loc_45588C]
add ecx, [loc_455890]
add edx, [loc_455894]
add ebp, [loc_455898]
mov esi, loc_445888
mov eax, [loc_44184C]
shr eax, 0x2
push eax
jmp short loc_40B894
align 16
loc_40B890:
inc ebx
inc ecx
inc edx
inc ebp
loc_40B894:
and ebx, 0x3fff
and ecx, 0x3fff
and edx, 0x3fff
and ebp, 0x3fff
lea eax, [esi+ecx*4]
lea edi, [esi+ebx*4]
fld dword [eax]
fld st0
fmul st0, st3
fadd dword [edi]
fst dword [edi]
fmul st0, st2
faddp st1, st0
lea edi, [esi+edx*4]
fld dword [edi]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [eax]
fmul st0, st2
faddp st1, st0
lea eax, [esi+ebp*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [edi]
fmul st0, st2
faddp st1, st0
fstp dword [eax]
inc ebx
inc ecx
inc edx
inc ebp
and ebx, 0x3fff
and ecx, 0x3fff
and edx, 0x3fff
and ebp, 0x3fff
lea eax, [esi+ecx*4]
lea edi, [esi+ebx*4]
fld dword [eax]
fld st0
fmul st0, st3
fadd dword [edi]
fst dword [edi]
fmul st0, st2
faddp st1, st0
lea edi, [esi+edx*4]
fld dword [edi]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [eax]
fmul st0, st2
faddp st1, st0
lea eax, [esi+ebp*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [edi]
fmul st0, st2
faddp st1, st0
fstp dword [eax]
inc ebx
inc ecx
inc edx
inc ebp
and ebx, 0x3fff
and ecx, 0x3fff
and edx, 0x3fff
and ebp, 0x3fff
lea eax, [esi+ecx*4]
lea edi, [esi+ebx*4]
fld dword [eax]
fld st0
fmul st0, st3
fadd dword [edi]
fst dword [edi]
fmul st0, st2
faddp st1, st0
lea edi, [esi+edx*4]
fld dword [edi]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [eax]
fmul st0, st2
faddp st1, st0
lea eax, [esi+ebp*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [edi]
fmul st0, st2
faddp st1, st0
fstp dword [eax]
inc ebx
inc ecx
inc edx
inc ebp
and ebx, 0x3fff
and ecx, 0x3fff
and edx, 0x3fff
and ebp, 0x3fff
lea eax, [esi+ecx*4]
lea edi, [esi+ebx*4]
fld dword [eax]
fld st0
fmul st0, st3
fadd dword [edi]
fst dword [edi]
fmul st0, st2
faddp st1, st0
lea edi, [esi+edx*4]
fld dword [edi]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [eax]
fmul st0, st2
faddp st1, st0
lea eax, [esi+ebp*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [edi]
fmul st0, st2
faddp st1, st0
fstp dword [eax]
dec dword [esp]
jnz near loc_40B890
pop eax
fstp st0
fstp st0
pop edi
pop esi
pop ebp
pop edx
pop ebx
ret
align 16
loc_40BA10:
push ebx
push edx
push esi
fld dword [loc_419690]
fld dword [loc_419694]
mov eax, ecx
mov ebx, ecx
mov edx, ecx
add eax, [loc_45588C]
add ebx, [loc_455890]
add ecx, [loc_455894]
add edx, [loc_455898]
mov esi, loc_445888
lea eax, [esi+eax*4]
lea ebx, [esi+ebx*4]
lea ecx, [esi+ecx*4]
lea edx, [esi+edx*4]
mov esi, [loc_44184C]
shr esi, 0x2
jmp short loc_40BA6C
align 16
loc_40BA60:
lea eax, [eax+0x4]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
lea edx, [edx+0x4]
loc_40BA6C:
fld dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fst dword [eax]
fmul st0, st2
faddp st1, st0
fld dword [ecx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ebx]
fmul st0, st2
faddp st1, st0
fld dword [edx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ecx]
fmul st0, st2
faddp st1, st0
fstp dword [edx]
lea eax, [eax+0x4]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
lea edx, [edx+0x4]
fld dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fst dword [eax]
fmul st0, st2
faddp st1, st0
fld dword [ecx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ebx]
fmul st0, st2
faddp st1, st0
fld dword [edx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ecx]
fmul st0, st2
faddp st1, st0
fstp dword [edx]
lea eax, [eax+0x4]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
lea edx, [edx+0x4]
fld dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fst dword [eax]
fmul st0, st2
faddp st1, st0
fld dword [ecx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ebx]
fmul st0, st2
faddp st1, st0
fld dword [edx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ecx]
fmul st0, st2
faddp st1, st0
fstp dword [edx]
lea eax, [eax+0x4]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
lea edx, [edx+0x4]
fld dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fst dword [eax]
fmul st0, st2
faddp st1, st0
fld dword [ecx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ebx]
fmul st0, st2
faddp st1, st0
fld dword [edx]
fxch st0, st1
fld st1
fmul st0, st4
faddp st1, st0
fst dword [ecx]
fmul st0, st2
faddp st1, st0
fstp dword [edx]
dec esi
jnz near loc_40BA60
fstp st0
fstp st0
pop esi
pop edx
pop ebx
ret
align 16
loc_40BB60:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40BBB0
align 16
loc_40BBB0:
and ecx, 0x3fff
fld dword [ecx*4+loc_445888]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fld st0
fadd dword [loc_4558FC]
fmul st0, st4
fadd dword [ebp]
fstp dword [ebp]
fst dword [loc_4558FC]
fadd dword [ebp+0x4]
fstp dword [ebp+0x4]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fld st0
fadd dword [loc_455900]
fmul st0, st4
fadd dword [eax]
fstp dword [eax]
fst dword [loc_455900]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
lea ebp, [ebp+0x8]
lea ebx, [ebx+0x4]
lea edx, [edx+0x4]
inc ecx
cmp ebp, esi
jb near loc_40BBB0
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40BD10:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40BD60
align 16
loc_40BD60:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, edx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
add eax, [loc_4558B8]
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
add eax, edx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558C0]
add eax, edx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
mov eax, [loc_4558E0]
add eax, edx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fld st0
fadd dword [loc_4558FC]
fmul st0, st4
fadd dword [ebp]
fstp dword [ebp]
fst dword [loc_4558FC]
fadd dword [ebp+0x4]
fstp dword [ebp+0x4]
mov eax, [loc_4558EC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
mov eax, [loc_4558F0]
add eax, edx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fld st0
fadd dword [loc_455900]
fmul st0, st4
fadd dword [eax]
fstp dword [eax]
fst dword [loc_455900]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
lea ebp, [ebp+0x8]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
inc edx
cmp ebp, esi
jb near loc_40BD60
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40BF20:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40BF70
align 16
loc_40BF70:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
add eax, ebx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, ebx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558D0]
add eax, ebx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
add eax, ebx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558D8]
add eax, ebx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558E8]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
fld st0
fadd dword [loc_4558FC]
fmul st0, st4
fadd dword [ebp]
fstp dword [ebp]
fst dword [loc_4558FC]
fadd dword [ebp+0x4]
fstp dword [ebp+0x4]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558F8]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
lea eax, [ebp+0x400]
fld st0
fadd dword [loc_455900]
fmul st0, st4
fadd dword [eax]
fstp dword [eax]
fst dword [loc_455900]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
lea ebp, [ebp+0x8]
lea edx, [edx+0x4]
lea ecx, [ecx+0x4]
inc ebx
cmp ebp, esi
jb near loc_40BF70
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40C130:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40C180
align 16
loc_40C180:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fld st0
fadd dword [loc_4558FC]
fmul st0, st4
fadd dword [ebp]
fstp dword [ebp]
fst dword [loc_4558FC]
fadd dword [ebp+0x4]
fstp dword [ebp+0x4]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fld st0
fadd dword [loc_455900]
fmul st0, st4
fadd dword [eax]
fstp dword [eax]
fst dword [loc_455900]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
lea ebp, [ebp+0x8]
lea ebx, [ebx+0x4]
lea edx, [edx+0x4]
lea ecx, [ecx+0x4]
cmp ebp, esi
jb near loc_40C180
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
loc_40C950:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40C9A0
align 16
loc_40C9A0:
and ecx, 0x3fff
fld dword [ecx*4+loc_445888]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fadd dword [ebp]
fstp dword [ebp]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fadd dword [eax]
fstp dword [eax]
lea ebp, [ebp+0x4]
lea ebx, [ebx+0x4]
lea edx, [edx+0x4]
inc ecx
cmp ebp, esi
jb near loc_40C9A0
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40CAE0:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40CB30
align 16
loc_40CB30:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, edx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
add eax, [loc_4558B8]
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
add eax, edx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558C0]
add eax, edx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
mov eax, [loc_4558E0]
add eax, edx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fadd dword [ebp]
fstp dword [ebp]
mov eax, [loc_4558EC]
add eax, edx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
mov eax, [loc_4558F0]
add eax, edx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fadd dword [eax]
fstp dword [eax]
lea ebp, [ebp+0x4]
lea ebx, [ebx+0x4]
lea ecx, [ecx+0x4]
inc edx
cmp ebp, esi
jb near loc_40CB30
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40CCC0:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40CD10
align 16
loc_40CD10:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
add eax, ebx
and eax, 0x3fff
fld dword [eax*4+loc_445888]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, ebx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558D0]
add eax, ebx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
add eax, ebx
and eax, 0x3fff
lea edi, [eax*4+loc_445888]
mov eax, [loc_4558D8]
add eax, ebx
and eax, 0x3fff
lea eax, [eax*4+loc_445888]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558E8]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
fadd dword [ebp]
fstp dword [ebp]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
mov eax, [loc_4558F8]
add eax, ebx
and eax, 0x3fff
fadd dword [eax*4+loc_445888]
lea eax, [ebp+0x400]
fadd dword [eax]
fstp dword [eax]
lea ebp, [ebp+0x4]
lea edx, [edx+0x4]
lea ecx, [ecx+0x4]
inc ebx
cmp ebp, esi
jb near loc_40CD10
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
align 16
loc_40CEA0:
fld dword [loc_419690]
fld dword [loc_419694]
fld dword [loc_4558A4]
fld dword [loc_4558A8]
add ecx, [loc_455898]
lea ecx, [ecx*4+loc_445888]
lea edx, [edx*4+loc_445888]
push ebx
mov ebx, [esp+0x8]
lea ebx, [ebx*4+loc_445888]
push ebp
push esi
push edi
mov ebp, loc_441048
mov eax, [loc_441848]
lea esi, [ebp+eax*4]
jmp short loc_40CEF0
align 16
loc_40CEF0:
fld dword [ecx]
fld st1
fmul dword [loc_4558AC]
mov eax, [loc_4558B4]
fld dword [ebx+eax*4]
fmul dword [loc_4558B0]
faddp st1, st0
fst st2
mov eax, [loc_4558B8]
lea eax, [edx+eax*4]
fld dword [eax]
fxch st0, st1
fld st1
fmul st0, st7
faddp st1, st0
fadd st0, st2
fst dword [edx]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558BC]
lea edi, [edx+eax*4]
mov eax, [loc_4558C0]
lea eax, [edx+eax*4]
fld dword [eax]
fld st0
fmul st0, st6
fadd dword [edi]
fst dword [edi]
fmul st0, st5
faddp st1, st0
fstp dword [eax]
fld st2
fmul dword [loc_4558C8]
mov eax, [loc_4558CC]
fld dword [edx+eax*4]
fmul dword [loc_4558C4]
faddp st1, st0
fst st3
mov eax, [loc_4558D0]
lea eax, [ebx+eax*4]
faddp st1, st0
fld dword [eax]
fld st0
fmul st0, st6
faddp st2, st0
fxch st0, st1
fst dword [ebx]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558D4]
lea edi, [ebx+eax*4]
mov eax, [loc_4558D8]
lea eax, [ebx+eax*4]
fld dword [eax]
fld st0
fmul st0, st5
fadd dword [edi]
fst dword [edi]
fmul st0, st4
faddp st1, st0
fstp dword [eax]
mov eax, [loc_4558DC]
fld dword [edx+eax*4]
mov eax, [loc_4558E0]
fadd dword [edx+eax*4]
mov eax, [loc_4558E4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558E8]
fadd dword [ebx+eax*4]
fadd dword [ebp]
fstp dword [ebp]
mov eax, [loc_4558EC]
fld dword [edx+eax*4]
mov eax, [loc_4558F0]
fadd dword [edx+eax*4]
mov eax, [loc_4558F4]
fadd dword [ebx+eax*4]
mov eax, [loc_4558F8]
fadd dword [ebx+eax*4]
lea eax, [ebp+0x400]
fadd dword [eax]
fstp dword [eax]
lea ebp, [ebp+0x4]
lea ebx, [ebx+0x4]
lea edx, [edx+0x4]
lea ecx, [ecx+0x4]
cmp ebp, esi
jb near loc_40CEF0
pop edi
pop esi
pop ebp
pop ebx
fstp dword [loc_4558A8]
fstp dword [loc_4558A4]
fstp st0
fstp st0
ret 0x4
loc_40D600:
push ebx
push ebp
mov edx, loc_441048
fld dword [loc_41B6FC]
fld dword [loc_4196A0]
fld dword [loc_4196A4]
mov eax, [loc_441848]
lea ebx, [edx+eax*4]
lea ebp, [edx+0x400]
jmp short loc_40D630
align 16
loc_40D630:
fld dword [edx]
fmul st0, st3
fld st0
fabs
fcomp st0, st3
fnstsw ax
test ah, 0x41
jz short loc_40D6A0
loc_40D641:
fistp word [ecx]
fld dword [ebp]
fmul st0, st3
fld st0
fabs
fcomp st0, st3
fnstsw ax
test ah, 0x41
jz short loc_40D6B4
loc_40D655:
fistp word [ecx+0x2]
fld dword [edx+0x4]
fmul st0, st3
fld st0
fabs
fcomp st0, st3
fnstsw ax
test ah, 0x41
jz short loc_40D6C8
loc_40D66A:
fistp word [ecx+0x4]
fld dword [ebp+0x4]
fmul st0, st3
fld st0
fabs
fcomp st0, st3
fnstsw ax
test ah, 0x41
jz short loc_40D6DC
loc_40D67F:
fistp word [ecx+0x6]
lea edx, [edx+0x8]
lea ebp, [ebp+0x8]
lea ecx, [ecx+0x8]
cmp edx, ebx
jb short loc_40D630
fstp st0
fstp st0
fstp st0
pop ebp
pop ebx
ret
align 16
loc_40D6A0:
fcomp st0, st2
fnstsw ax
test ah, 0x41
jz short loc_40D6AD
fld st0
jmp short loc_40D641
loc_40D6AD:
fld st1
jmp short loc_40D641
align 4
loc_40D6B4:
fcomp st0, st1
fnstsw ax
test ah, 0x41
jnz short loc_40D6C1
fld st1
jmp short loc_40D655
loc_40D6C1:
fld st0
jmp short loc_40D655
align 8
loc_40D6C8:
fcomp st0, st1
fnstsw ax
test ah, 0x41
jnz short loc_40D6D5
fld st1
jmp short loc_40D66A
loc_40D6D5:
fld st0
jmp short loc_40D66A
align 4
loc_40D6DC:
fcomp st0, st1
fnstsw ax
test ah, 0x41
jnz short loc_40D6E9
fld st1
jmp short loc_40D67F
loc_40D6E9:
fld st0
jmp short loc_40D67F
align 16
loc_40D6F0:
push ebx
push ecx
push ecx
fld dword [ecx+0x14]
fld dword [ecx+0x1c]
fld dword [ecx+0xc]
fld dword [ecx+0x20]
fld dword [ecx+0x10]
mov ebx, [ecx+0x8]
mov eax, [loc_441848]
lea ecx, [edx+eax*4]
jmp short loc_40D718
align 16
loc_40D710:
cmp edx, ecx
jae near loc_40D8A0
loc_40D718:
mov eax, [edx]
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D748
fsub st0, st4
loc_40D748:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x4]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D777
fsub st0, st4
loc_40D777:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x8]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D7A6
fsub st0, st4
loc_40D7A6:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0xc]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D7D5
fsub st0, st4
loc_40D7D5:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x10]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D804
fsub st0, st4
loc_40D804:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x14]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D833
fsub st0, st4
loc_40D833:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x18]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40D862
fsub st0, st4
loc_40D862:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x1c]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x20]
test ah, 0x1
jnz near loc_40D710
fsub st0, st4
cmp edx, ecx
jb near loc_40D718
loc_40D8A0:
pop ecx
pop ecx
fstp dword [ecx+0x10]
fstp st0
fstp st0
fstp st0
fstp st0
pop ebx
ret
align 16
loc_40D8B0:
push ebx
push ecx
push ecx
fld dword [ecx+0x14]
fld dword [ecx+0x1c]
fld dword [ecx+0xc]
fld dword [ecx+0x20]
fld dword [ecx+0x10]
mov ebx, [ecx+0x8]
mov eax, [loc_441848]
lea ecx, [edx+eax*4]
jmp short loc_40D8D8
align 16
loc_40D8D0:
cmp edx, ecx
jae near loc_40DA7C
loc_40D8D8:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40D90B
fsub st0, st4
loc_40D90B:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40D93E
fsub st0, st4
loc_40D93E:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40D971
fsub st0, st4
loc_40D971:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40D9A4
fsub st0, st4
loc_40D9A4:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40D9D7
fsub st0, st4
loc_40D9D7:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40DA0A
fsub st0, st4
loc_40DA0A:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40DA3D
fsub st0, st4
loc_40DA3D:
fist dword [esp]
mov eax, [esp]
lea eax, [ebx+eax*2]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
fild word [eax]
fild word [eax+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz near loc_40D8D0
fsub st0, st4
cmp edx, ecx
jb near loc_40D8D8
loc_40DA7C:
pop ecx
pop ecx
fstp dword [ecx+0x10]
fstp st0
fstp st0
fstp st0
fstp st0
pop ebx
ret
align 16
loc_40DA90:
push ebx
lea edx, [ecx+edx*4]
xor eax, eax
jmp short loc_40DA9B
align 16
loc_40DA9B:
mov ebx, [ecx]
mov [ecx], eax
mov [ecx+0x4], eax
mov [ecx+0x8], eax
mov [ecx+0xc], eax
mov [ecx+0x10], eax
mov [ecx+0x14], eax
mov [ecx+0x18], eax
mov [ecx+0x1c], eax
mov ebx, [ecx+0x20]
mov [ecx+0x20], eax
mov [ecx+0x24], eax
mov [ecx+0x28], eax
mov [ecx+0x2c], eax
mov [ecx+0x30], eax
mov [ecx+0x34], eax
mov [ecx+0x38], eax
mov [ecx+0x3c], eax
mov ebx, [ecx+0x40]
mov [ecx+0x40], eax
mov [ecx+0x44], eax
mov [ecx+0x48], eax
mov [ecx+0x4c], eax
mov [ecx+0x50], eax
mov [ecx+0x54], eax
mov [ecx+0x58], eax
mov [ecx+0x5c], eax
mov ebx, [ecx+0x60]
mov [ecx+0x60], eax
mov [ecx+0x64], eax
mov [ecx+0x68], eax
mov [ecx+0x6c], eax
mov [ecx+0x70], eax
mov [ecx+0x74], eax
mov [ecx+0x78], eax
mov [ecx+0x7c], eax
lea ecx, [ecx+0x80]
cmp ecx, edx
jb short loc_40DA9B
pop ebx
ret
align 16
loc_40DB20:
fld dword [loc_4196AC]
fldz
fld dword [esp+0x4]
push ecx
push ecx
xor ecx, ecx
fcom st0, st1
fnstsw ax
test ah, 0x1
jz near loc_40DBE0
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fadd st0, st2
fcom st0, st1
fnstsw ax
test ah, 0x1
jz short loc_40DBA4
inc ecx
fld st0
fsubp st1, st0
jmp short loc_40DBA4
align 4
loc_40DBA4:
fistp dword [esp]
fld dword [ecx*4+loc_418794]
mov eax, [esp]
and eax, 0xff
fmul dword [eax*4+loc_4181F8]
mov eax, [esp]
shr eax, 0x8
and eax, 0xff
fmul dword [eax*4+loc_4185F8]
fstp st2
fstp st0
pop ecx
pop ecx
ret 0x4
align 16
loc_40DBE0:
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fsub st0, st2
fcom st0, st2
fnstsw ax
test ah, 0x41
jnz short loc_40DC50
inc ecx
fld st0
fsubp st1, st0
jmp short loc_40DC50
align 16
loc_40DC50:
fistp dword [esp]
fld dword [ecx*4+loc_418770]
mov eax, [esp]
and eax, 0xff
fmul dword [eax*4+loc_4181F8]
mov eax, [esp]
shr eax, 0x8
and eax, 0xff
fmul dword [eax*4+loc_4185F8]
fstp st2
fstp st0
pop ecx
pop ecx
ret 0x4
loc_40DD90:
push ebx
push ebp
push ecx
push ecx
fld dword [ecx+0x14]
fld dword [ecx+0x1c]
fld dword [ecx+0xc]
fld dword [ecx+0x20]
fld dword [ecx+0x10]
mov ebx, [ecx+0x8]
mov eax, [loc_441848]
lea ecx, [edx+eax*4]
jmp short loc_40DDB8
loc_40DDB0:
cmp edx, ecx
jae near loc_40DFD8
loc_40DDB8:
mov eax, [edx]
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DDFB
fsub st0, st4
loc_40DDFB:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x4]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DE3D
fsub st0, st4
loc_40DE3D:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x8]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DE7F
fsub st0, st4
loc_40DE7F:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0xc]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DEC1
fsub st0, st4
loc_40DEC1:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x10]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DF03
fsub st0, st4
loc_40DF03:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x14]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DF45
fsub st0, st4
loc_40DF45:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x18]
fadd st0, st2
fcom st0, st3
fnstsw ax
test ah, 0x1
jnz short loc_40DF87
fsub st0, st4
loc_40DF87:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fstp dword [edx+0x1c]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x20]
test ah, 0x1
jnz near loc_40DDB0
fsub st0, st4
cmp edx, ecx
jb near loc_40DDB8
loc_40DFD8:
pop ecx
pop ecx
fstp dword [ecx+0x10]
fstp st0
fstp st0
fstp st0
fstp st0
pop ebp
pop ebx
ret
align 16
loc_40DFF0:
push ebx
push ebp
push ecx
push ecx
fld dword [ecx+0x14]
fld dword [ecx+0x1c]
fld dword [ecx+0xc]
fld dword [ecx+0x20]
fld dword [ecx+0x10]
mov ebx, [ecx+0x8]
mov eax, [loc_441848]
lea ecx, [edx+eax*4]
jmp short loc_40E018
loc_40E010:
cmp edx, ecx
jae near loc_40E254
loc_40E018:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E05E
fsub st0, st4
loc_40E05E:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E0A4
fsub st0, st4
loc_40E0A4:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E0EA
fsub st0, st4
loc_40E0EA:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E130
fsub st0, st4
loc_40E130:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E176
fsub st0, st4
loc_40E176:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E1BC
fsub st0, st4
loc_40E1BC:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz short loc_40E202
fsub st0, st4
loc_40E202:
fist dword [esp]
mov eax, [esp]
lea ebp, [eax+ebx]
fild dword [esp]
fld st1
fxch st0, st1
fsubp st1, st0
xor eax, eax
mov ah, [ebp]
mov [esp], ax
mov ah, [ebp+0x1]
mov [esp+0x2], ax
fild word [esp]
fild word [esp+0x2]
fsub st0, st1
fmulp st2, st0
faddp st1, st0
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fadd st0, st2
fcom st0, st3
fnstsw ax
lea edx, [edx+0x4]
test ah, 0x1
jnz near loc_40E010
fsub st0, st4
cmp edx, ecx
jb near loc_40E018
loc_40E254:
pop ecx
pop ecx
fstp dword [ecx+0x10]
fstp st0
fstp st0
fstp st0
fstp st0
pop ebp
pop ebx
ret
align 16
loc_40E270:
fld dword [edx+0xc]
fld dword [edx+0x10]
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push esi
mov eax, [loc_441848]
lea esi, [eax*4+loc_441048]
mov eax, loc_441048
mov edx, loc_441448
mov ecx, loc_455904
nop
nop
nop
loc_40E2AC:
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul st0, st5
fld dword [ecx]
fld st0
fmul st0, st2
fadd dword [eax]
fstp dword [eax]
fmul st0, st2
fadd dword [edx]
fstp dword [edx]
fld dword [ecx+0x4]
fmul st1, st0
fmulp st2, st0
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edx+0x4]
fstp dword [edx+0x4]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul st0, st5
fld dword [ecx+0x8]
fld st0
fmul st0, st2
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fmul st0, st2
fadd dword [edx+0x8]
fstp dword [edx+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmulp st2, st0
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edx+0xc]
fstp dword [edx+0xc]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul st0, st5
fld dword [ecx+0x10]
fld st0
fmul st0, st2
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fmul st0, st2
fadd dword [edx+0x10]
fstp dword [edx+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmulp st2, st0
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edx+0x14]
fstp dword [edx+0x14]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul st0, st5
fld dword [ecx+0x18]
fld st0
fmul st0, st2
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fmul st0, st2
fadd dword [edx+0x18]
fstp dword [edx+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmulp st2, st0
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edx+0x1c]
fstp dword [edx+0x1c]
lea eax, [eax+0x20]
lea edx, [edx+0x20]
lea ecx, [ecx+0x20]
cmp eax, esi
jb near loc_40E2AC
fstp st0
fstp st0
fstp st0
fstp st0
pop esi
ret 0x4
align 16
loc_40E390:
fld dword [edx+0x38]
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push esi
push edi
push ebx
mov eax, [loc_441848]
lea esi, [eax*4+loc_441048]
mov eax, loc_441048
mov ebx, loc_441448
mov ecx, loc_455904
mov edi, [loc_44586C]
nop
nop
loc_40E3D0:
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx]
fld st0
fmul st0, st4
fadd dword [edi]
fstp dword [edi]
fld st0
fmul st0, st3
fadd dword [eax]
fstp dword [eax]
fmul st0, st1
fadd dword [ebx]
fstp dword [ebx]
fld dword [ecx+0x4]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edi+0x4]
fstp dword [edi+0x4]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x8]
fld st0
fmul st0, st4
fadd dword [edi+0x8]
fstp dword [edi+0x8]
fld st0
fmul st0, st3
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fmul st0, st1
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0xc]
fstp dword [ebx+0xc]
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edi+0xc]
fstp dword [edi+0xc]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x10]
fld st0
fmul st0, st4
fadd dword [edi+0x10]
fstp dword [edi+0x10]
fld st0
fmul st0, st3
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fmul st0, st1
fadd dword [ebx+0x10]
fstp dword [ebx+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x14]
fstp dword [ebx+0x14]
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edi+0x14]
fstp dword [edi+0x14]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x18]
fld st0
fmul st0, st4
fadd dword [edi+0x18]
fstp dword [edi+0x18]
fld st0
fmul st0, st3
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fmul st0, st1
fadd dword [ebx+0x18]
fstp dword [ebx+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x1c]
fstp dword [ebx+0x1c]
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edi+0x1c]
fstp dword [edi+0x1c]
lea eax, [eax+0x20]
lea ebx, [ebx+0x20]
lea ecx, [ecx+0x20]
lea edi, [edi+0x20]
cmp eax, esi
jb near loc_40E3D0
fstp st0
fstp st0
fstp st0
pop ebx
pop edi
pop esi
ret 0x4
align 16
loc_40E520:
fld dword [edx+0x34]
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push esi
push edi
push ebx
mov eax, [loc_441848]
lea esi, [eax*4+loc_441048]
mov eax, loc_441048
mov ebx, loc_441448
mov ecx, loc_455904
mov edi, [loc_455888]
nop
nop
loc_40E560:
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx]
fld st0
fmul st0, st3
fadd dword [eax]
fstp dword [eax]
fmul st0, st1
fadd dword [ebx]
fstp dword [ebx]
fld dword [ecx+0x4]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edi]
fstp dword [edi]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x8]
fld st0
fmul st0, st3
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fmul st0, st1
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0xc]
fstp dword [ebx+0xc]
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edi+0x4]
fstp dword [edi+0x4]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x10]
fld st0
fmul st0, st3
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fmul st0, st1
fadd dword [ebx+0x10]
fstp dword [ebx+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x14]
fstp dword [ebx+0x14]
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edi+0x8]
fstp dword [edi+0x8]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x18]
fld st0
fmul st0, st3
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fmul st0, st1
fadd dword [ebx+0x18]
fstp dword [ebx+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x1c]
fstp dword [ebx+0x1c]
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edi+0xc]
fstp dword [edi+0xc]
lea eax, [eax+0x20]
lea ebx, [ebx+0x20]
lea ecx, [ecx+0x20]
lea edi, [edi+0x10]
cmp eax, esi
jb near loc_40E560
fstp st0
fstp st0
fstp st0
pop ebx
pop edi
pop esi
ret 0x4
align 16
loc_40E680:
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push edi
push esi
push ebp
push ebx
mov edi, [loc_455888]
mov esi, [loc_44586C]
mov eax, [loc_441848]
lea ebp, [eax*4+loc_441048]
mov eax, loc_441048
mov ebx, loc_441448
mov ecx, loc_455904
nop
nop
loc_40E6C4:
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx]
fld st0
fmul st0, st2
fadd dword [ebx]
fstp dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fstp dword [eax]
fmul st0, st4
fadd dword [esi]
fstp dword [esi]
fld dword [ecx+0x4]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edi]
fstp dword [edi]
fadd dword [esi+0x4]
fstp dword [esi+0x4]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x8]
fld st0
fmul st0, st2
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld st0
fmul st0, st3
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fmul st0, st4
fadd dword [esi+0x8]
fstp dword [esi+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0xc]
fstp dword [ebx+0xc]
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edi+0x4]
fstp dword [edi+0x4]
fadd dword [esi+0xc]
fstp dword [esi+0xc]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x10]
fld st0
fmul st0, st2
fadd dword [ebx+0x10]
fstp dword [ebx+0x10]
fld st0
fmul st0, st3
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fmul st0, st4
fadd dword [esi+0x10]
fstp dword [esi+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x14]
fstp dword [ebx+0x14]
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edi+0x8]
fstp dword [edi+0x8]
fadd dword [esi+0x14]
fstp dword [esi+0x14]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x18]
fld st0
fmul st0, st2
fadd dword [ebx+0x18]
fstp dword [ebx+0x18]
fld st0
fmul st0, st3
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fmul st0, st4
fadd dword [esi+0x18]
fstp dword [esi+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x1c]
fstp dword [ebx+0x1c]
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edi+0xc]
fstp dword [edi+0xc]
fadd dword [esi+0x1c]
fstp dword [esi+0x1c]
lea eax, [eax+0x20]
lea ebx, [ebx+0x20]
lea ecx, [ecx+0x20]
lea edi, [edi+0x10]
lea esi, [esi+0x20]
cmp eax, ebp
jb near loc_40E6C4
fstp st0
fstp st0
pop ebx
pop ebp
pop esi
pop edi
ret 0x4
align 16
loc_40E840:
fld dword [edx+0x34]
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push esi
push edi
push ebx
mov eax, [loc_441848]
lea esi, [eax*4+loc_441048]
mov eax, loc_441048
mov ebx, loc_441448
mov ecx, loc_455904
mov edi, [loc_455888]
nop
nop
loc_40E880:
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx]
fld st0
fmul st0, st4
fadd dword [edi]
fstp dword [edi]
fld st0
fmul st0, st3
fadd dword [eax]
fstp dword [eax]
fmul st0, st1
fadd dword [ebx]
fstp dword [ebx]
fld dword [ecx+0x4]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edi+0x4]
fstp dword [edi+0x4]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x8]
fld st0
fmul st0, st4
fadd dword [edi+0x8]
fstp dword [edi+0x8]
fld st0
fmul st0, st3
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fmul st0, st1
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0xc]
fstp dword [ebx+0xc]
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edi+0xc]
fstp dword [edi+0xc]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x10]
fld st0
fmul st0, st4
fadd dword [edi+0x10]
fstp dword [edi+0x10]
fld st0
fmul st0, st3
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fmul st0, st1
fadd dword [ebx+0x10]
fstp dword [ebx+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x14]
fstp dword [ebx+0x14]
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edi+0x14]
fstp dword [edi+0x14]
fadd st0, st1
fld st0
fmul st0, st3
fld st1
fmul dword [edx+0xc]
fld st2
fmul dword [edx+0x10]
fld dword [ecx+0x18]
fld st0
fmul st0, st4
fadd dword [edi+0x18]
fstp dword [edi+0x18]
fld st0
fmul st0, st3
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fmul st0, st1
fadd dword [ebx+0x18]
fstp dword [ebx+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmul st2, st0
fmulp st3, st0
fadd dword [ebx+0x1c]
fstp dword [ebx+0x1c]
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edi+0x1c]
fstp dword [edi+0x1c]
lea eax, [eax+0x20]
lea ebx, [ebx+0x20]
lea ecx, [ecx+0x20]
lea edi, [edi+0x20]
cmp eax, esi
jb near loc_40E880
fstp st0
fstp st0
fstp st0
pop ebx
pop edi
pop esi
ret 0x4
align 16
loc_40E9D0:
fld dword [ecx+0x4]
fld dword [esp+0x4]
fmul dword [edx+0x14]
fst dword [ecx+0x4]
fsub st0, st1
fmul dword [loc_455D04]
fxch st0, st1
push edi
push esi
push ebp
push ebx
mov edi, [loc_455888]
mov esi, [loc_44586C]
mov eax, [loc_441848]
lea ebp, [eax*4+loc_441048]
mov eax, loc_441048
mov ebx, loc_441448
mov ecx, loc_455904
nop
nop
loc_40EA14:
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx]
fld st0
fmul st0, st2
fadd dword [ebx]
fstp dword [ebx]
fld st0
fmul st0, st3
fadd dword [eax]
fstp dword [eax]
fld st0
fmul st0, st4
fadd dword [edi]
fstp dword [edi]
fmul st0, st4
fadd dword [esi]
fstp dword [esi]
fld dword [ecx+0x4]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x4]
fstp dword [ebx+0x4]
fadd dword [eax+0x4]
fstp dword [eax+0x4]
fadd dword [edi+0x4]
fstp dword [edi+0x4]
fadd dword [esi+0x4]
fstp dword [esi+0x4]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x8]
fld st0
fmul st0, st2
fadd dword [ebx+0x8]
fstp dword [ebx+0x8]
fld st0
fmul st0, st3
fadd dword [eax+0x8]
fstp dword [eax+0x8]
fld st0
fmul st0, st4
fadd dword [edi+0x8]
fstp dword [edi+0x8]
fmul st0, st4
fadd dword [esi+0x8]
fstp dword [esi+0x8]
fld dword [ecx+0xc]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0xc]
fstp dword [ebx+0xc]
fadd dword [eax+0xc]
fstp dword [eax+0xc]
fadd dword [edi+0xc]
fstp dword [edi+0xc]
fadd dword [esi+0xc]
fstp dword [esi+0xc]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x10]
fld st0
fmul st0, st2
fadd dword [ebx+0x10]
fstp dword [ebx+0x10]
fld st0
fmul st0, st3
fadd dword [eax+0x10]
fstp dword [eax+0x10]
fld st0
fmul st0, st4
fadd dword [edi+0x10]
fstp dword [edi+0x10]
fmul st0, st4
fadd dword [esi+0x10]
fstp dword [esi+0x10]
fld dword [ecx+0x14]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x14]
fstp dword [ebx+0x14]
fadd dword [eax+0x14]
fstp dword [eax+0x14]
fadd dword [edi+0x14]
fstp dword [edi+0x14]
fadd dword [esi+0x14]
fstp dword [esi+0x14]
fadd st0, st1
fld st0
fmul dword [edx+0x38]
fld st1
fmul dword [edx+0x34]
fld st2
fmul dword [edx+0xc]
fld st3
fmul dword [edx+0x10]
fld dword [ecx+0x18]
fld st0
fmul st0, st2
fadd dword [ebx+0x18]
fstp dword [ebx+0x18]
fld st0
fmul st0, st3
fadd dword [eax+0x18]
fstp dword [eax+0x18]
fld st0
fmul st0, st4
fadd dword [edi+0x18]
fstp dword [edi+0x18]
fmul st0, st4
fadd dword [esi+0x18]
fstp dword [esi+0x18]
fld dword [ecx+0x1c]
fmul st1, st0
fmul st2, st0
fmul st3, st0
fmulp st4, st0
fadd dword [ebx+0x1c]
fstp dword [ebx+0x1c]
fadd dword [eax+0x1c]
fstp dword [eax+0x1c]
fadd dword [edi+0x1c]
fstp dword [edi+0x1c]
fadd dword [esi+0x1c]
fstp dword [esi+0x1c]
lea eax, [eax+0x20]
lea ebx, [ebx+0x20]
lea ecx, [ecx+0x20]
lea edi, [edi+0x20]
lea esi, [esi+0x20]
cmp eax, ebp
jb near loc_40EA14
fstp st0
fstp st0
pop ebx
pop ebp
pop esi
pop edi
ret 0x4
loc_40EBB5:
