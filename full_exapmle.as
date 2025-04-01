.extern EXT_FUNC

MAIN:   mov     #5, @r1
        add     @r1, NUM
        jsr     EXT_FUNC
        prn     VALUE
        stop

NUM:    .data   12, -8
VALUE:  .data   4
STR:    .string "hi"

.entry MAIN
.entry STR
