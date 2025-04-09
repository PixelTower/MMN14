; Example assembly file for MMN14 project

macro PRINT_HELLO
    mov r2, r3
    add r2, r1
endmacro

.entry START
.extern EXT_LABEL

START:  mov r1, r2
        PRINT_HELLO
        jmp EXT_LABEL
        stop
