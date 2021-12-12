
;  ------------------------------------------------------------------------
;    File Name: keyboard_interrupt.asm
;       Author: Zhao Yanbai
;               2021-10-29 23:20:37 Friday CST
;  Description: 
;   初始化8259将其中断向量号设置为0x20
;   中断EOI方式设置为手动EOI
;   并禁用所有中断，只开启键盘中断
;   每收到一次键盘中断，就将屏幕上显示的字符变化一下
;  ------------------------------------------------------------------------


BITS 16
ORG 0x7C00
IntVect EQU 0x20
_start:
    jmp 0x0000:entry
entry:
    mov ax, cs
    mov ds, ax
    mov ss, ax
    mov sp, 0x7C00

    ; 调用BIOS清屏，并设置为80x25的彩色文本模式
    ; 功能号: 0x00
    ; 用途: 设置显示模式
    ; 参数: AL = 显示模式号
    ;       AL=0x00: 40x25黑白文本
    ;       AL=0x01: 40x25彩色文本
    ;       AL=0x02: 80x25黑白文本
    ;       AL=0x03: 80x25彩色文本
    ;       ...
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    ; 将es设为显存段地址
    mov ax, 0xB800
    mov es, ax

    ; 在中断向量表中设置键盘中断程序入口地址
    mov bx, (IntVect+1)*4
    mov ax, ds
    mov cx, kbd_isr
    mov [bx + 0x00], cx
    mov [bx + 0x02], ax

    ; 准备初始化8259
    cli

    ; 先初始化主片
    ; ICW1: 需要ICW4，级连状态
    mov al, 0001_0001b
    out 0x20, al

    ; ICW2: 中断向量地址为0x20
    mov al, IntVect
    out 0x21, al

    ; ICW3: 主片2号IR输入引脚连着从片
    mov al, 0000_0100b
    out 0x21, al

    ; ICW4: 非缓冲，手动发送EOI的80x86模式
    mov al, 0000_0001b
    out 0x21, al

    ; 再初始化从片
    ; ICW1: 需要ICW4，级连状态
    mov al, 0001_0001b
    out 0xA0, al

    ; ICW2: 中断向量地址为0x28
    mov al, IntVect+0x08
    out 0xA1, al

    ; ICW3: 从片连在主片的2号IR输入引脚
    mov al, 0000_0010b
    out 0xA1, al

    ; ICW4: 非缓冲，手动发送EOI的80x86模式
    mov al, 0000_0001b
    out 0xA1, al

    ; 主片OCW1: 解除主片上键盘的中断屏蔽
    mov al, 1111_1101b
    out 0x21, al

    ; 从片OCW1: 屏蔽从片上的所有中断
    mov al, 1111_1111b
    out 0xA1, al

    ; 打开CPU中断允许标志
    sti

run:
    hlt
    jmp run

kbd_isr:
    push ax
    push bx

    ; 从键盘缓冲区中读取输入
    in al, 0x60
    test al, 0x80
    jnz .ignore     ; 如果是break code就跳过

    ; 变化显示字符
    mov bl, [cnt]
    cmp bl, 26
    jbe .letter
    mov bl, 0
 .letter:
    mov al, bl
    add al, 'A'
    inc bl
    mov [cnt], bl

    mov byte [es:0], al
    mov byte [es:1], 0x0C

 .ignore:
    ; 给主片发送EOI
    ; OCW2
    mov al, 0110_0001b
    out 0x20, al

    pop bx
    pop ax
    iret

    cnt db 0
    times 510 - ($ - $$) db 0
    dw 0xAA55
