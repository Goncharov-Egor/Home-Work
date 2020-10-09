; вариант 7: Массив B из индексов положительных элементов A.

format PE console
entry start

include 'win32a.inc'

;--------------------------------------------------------------------------
section '.data' data readable writable

        strVecSize     db 'size of vector: ', 0
        strIncorSize   db 'Incorrect size of vector = %d', 10, 0
        strVecElemI    db '[%d]? ', 0
        strScanInt     db '%d', 0
        strBVec        db 'B:', 10, 0
        strVecElemOut  db '[%d] = %d', 10, 0
        newline db '', 10, 0

        vec_size     dd 0
        count        dd 0
        i            dd ?
        i_b          dd ?
        tmp          dd ?
        tmp_b        dd ?
        tmpStack     dd ?
        vec          rd 100
        vecB         rd 100

;--------------------------------------------------------------------------
section '.code' code readable executable
start:
        xor esi, esi
        call VectorInput
        call SetDefoultValues
        call GenerateArrayB
        call SetDefoultValues
        call ReturnArrayB

        finish:
        call [getch]

        push 0
        call [ExitProcess]
;----------------------------------------------------------------------
VectorInput:
        push strVecSize
        call [printf]
        add esp, 4

        push vec_size
        push strScanInt
        call [scanf]
        add esp, 8

        mov eax, [vec_size]
        cmp eax, 0
        jg  getVector

; fail size
        push vec_size
        push strIncorSize
        call [printf]
        call [getch]
        push 0
        call [ExitProcess]
getVector:
        xor ecx, ecx
        mov ebx, vec
getVecLoop:
        mov [tmp], ebx
        cmp ecx, [vec_size]
        jge endInputVector

        mov [i], ecx
        push ecx
        push strVecElemI
        call [printf]
        add esp, 8

        push ebx
        push strScanInt
        call [scanf]
        add esp, 8

        mov ecx, [i]
        inc ecx
        mov ebx, [tmp]
        add ebx, 4
        jmp getVecLoop
endInputVector:
        mov ebx, vec
        xor ecx, ecx
        ret
;----------------------------------------------------------------
SetDefoultValues:
        xor ecx, ecx
        mov [i], 0
        xor eax, eax
        mov ebx, vec                 ; ebx = &vec
        mov edx, vecB                ; edx = &vecB
        ret

endScanVector:
        ret
;----------------------------------------------------------------
GenerateArrayB:
       cmp ecx, [vec_size]
       jge endScanVector
       mov eax, [ebx]
       cmp eax, 1
       jge addElement
       add ebx, 4
       add ecx, 1
       jmp GenerateArrayB

addElement:
        mov [edx], ecx
        add edx, 4
        add ebx, 4
        add ecx, 1
        add esi, 1
        jmp GenerateArrayB
;----------------------------------------------------------------
ReturnArrayB:
        mov [tmp], ecx
        push strBVec
        call [printf]
        mov ecx, [tmp]
        mov edx, vecB
        add esp, 4
        mov eax, [vec_size]
        sub eax, [count]
SaveNum:
        cmp ecx, esi
        jge theEnd
        mov [tmp], ecx
        mov [tmp_b], eax
        mov [i], edx
        push dword [edx]
        push ecx
        push strVecElemOut
        call [printf]
        add esp, 8
        mov ecx, [tmp]
        mov eax, [tmp_b]
        mov edx, [i]
        add edx, 4
        add ecx, 1
        jmp SaveNum
theEnd:
        jmp finish
;-------------------------------third act - including HeapApi--------------------------
                                                 
section '.idata' import data readable
    library kernel, 'kernel32.dll',\
            msvcrt, 'msvcrt.dll',\
            user32,'USER32.DLL'

include 'api\user32.inc'
include 'api\kernel32.inc'
    import kernel,\
           ExitProcess, 'ExitProcess',\
           HeapCreate,'HeapCreate',\
           HeapAlloc,'HeapAlloc'
  include 'api\kernel32.inc'
    import msvcrt,\
           printf, 'printf',\
           scanf, 'scanf',\
           getch, '_getch'