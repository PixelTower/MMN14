

START:    mov   r1, r2      ; Move the contents of register r1 to register r2
          cmp   r2, #10     ; Compare register r2 with immediate value 10
          add   r1, r3      ; Add register r1 and r3, store the result in r3
          sub   r3, r4      ; Subtract register r4 from r3, result in r3
          lea   DATA, r5    ; Load effective address of label DATA into r5
          prn   r5          ; Print the contents of register r5
          jmp   &LOOP       ; Jump (relative) to label LOOP
          stop              ; End of instructions

LOOP:     inc   r2          ; Increment register r2
          bne   &START      ; Branch to START if the Zero flag is not set

          mcro  double_inc  ; Start macro definition (double increment)
              inc r1
              inc r2
          mcroend           ; End of macro definition

          double_inc        ; Macro call: expands to two increment instructions

DATA:     .data 5, -3, 15 ; Data directive: allocates three integers
