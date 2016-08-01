; 《0dayp安全》3.2 shellcode 代码(nasm)
; 2016-07-20 22:00:21
    ADD     ESP, -0x80
    MOV     EBP, ESP
    XOR     EAX, EAX
    PUSH    EAX
    PUSH    0x74736556        ; 'tseV'
    PUSH    0x2E656341        ; '.ecA'
    MOV     EBX, ESP
    PUSH    EAX
    PUSH    EBX
    PUSH    EBX
    PUSH    EAX
    MOV     EBX, 0x77D507EA    ; MessageBoxA
    CALL    EBX

    PUSH    EAX
    MOV     EBX, 0x7C81CAFA    ; ExitProcess
    CALL    EBX

