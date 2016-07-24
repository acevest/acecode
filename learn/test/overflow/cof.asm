_main:
    ;INT3
    CLD

    PUSH        0xFFFFFFFF
    PUSH        0x1E380A6A              ; hash of MessageBoxA
    PUSH        0x4FD18963              ; hash of ExitProcess
    PUSH        0x0C917432              ; hash of LoadLibraryA


    XOR     EAX, EAX
    XOR     EDI, EDI
    MOV     EAX, [FS:EAX + 0x30]        ; PEB = TEB + 0x30
    MOV     EAX, [EAX + 0x0C]           ; PEB_LDR_DATA
    MOV     EAX, [EAX + 0x1C]           ; InInitializationOrderModuleList
    MOV     EAX, [EAX]                  ; Module Kernel32.dll; next 指针在首4字节
    MOV     EBP, [EAX + 0x08]           ; BaseAddr of Kernel32.dll

load_next_func_hash:
    POP         EBX

    CMP         EBX, 0xFFFFFFFF
    JE          load_func_finish

    CMP         EBX, 0x1E380A6A
    JNE         skip_load_library

    PUSH        0x3233                  ; '\0\023'
    PUSH        0x72657375              ; 'resu'
    PUSH        ESP
    LEA         EAX, [ESP + 0x10]
    MOV         EAX, [EAX]
    CALL        EAX
    ADD         ESP, 8


    XCHG        EAX, EBP                ; EBP -> user32.dll BaseAddr

skip_load_library:
    PUSHAD

    MOV         ECX, [EBP + 0x3C]       ;  Offset of PE Header
    ADD         ECX, EBP                ; Address of PE Header

    MOV         ECX, [ECX + 0x78]       ;  Offset of Export Table
    ADD         ECX, EBP                ; Address of Export Table


    MOV         EDI, -1

compare_next_func:

    INC         EDI

    MOV         ESI, [ECX + 0x20]       ;  Offset of Names Table
    ADD         ESI, EBP                ; Address of Names Table

    MOV         ESI, [ESI + EDI*4]      ;  Offset of Function Name
    ADD         ESI, EBP                ; Address of Function Name

    CDQ

get_func_hash:
    MOVSX       EAX, BYTE [ESI]
    CMP         AL, AH
    JZ          compare_hash
    ROR         EDX, 7
    ADD         EDX, EAX
    INC         ESI
    JMP         get_func_hash

compare_hash
    CMP         EDX, EBX
    JNZ         compare_next_func

    MOV         ESI, [ECX + 0x24]       ;  Offset of Ordinal Table
    ADD         ESI, EBP                ; Address of Ordinal Table

    XOR         EAX, EAX
    MOV         AX,  [ESI + 2*EDI]
    MOV         EDI, EAX


    MOV         ESI, [ECX + 0x1C]       ;  Offset of Address Table
    ADD         ESI, EBP                ; Address of Address Table

    MOV         EAX, [ESI + 4*EDI]
    ADD         EAX, EBP

    POP         EDI
    PUSH        EAX
    POPAD
    LEA         EAX, [ESP+0x0C]
    MOV         [EAX], EDI

    JMP         load_next_func_hash

load_func_finish:
    ;INT3
    MOV         EDI, ESP

    XOR         EAX, EAX
    PUSH        EAX
    PUSH        0x74736556              ; 'tseV'
    PUSH        0x2E656341              ; '.ecA'
    MOV         EBX, ESP
    PUSH        EAX
    PUSH        EBX
    PUSH        EBX
    PUSH        EAX
    CALL        [EDI + 8]               ; MessageBoxA('Ace.Vest')

    XOR         EAX, EAX
    PUSH        EAX
    CALL        [EDI + 4]               ; ExitProcess(0)
