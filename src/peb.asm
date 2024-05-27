section .text
    global GetPEB

GetPEB:
    mov rax, gs:[0x60]
    ret
