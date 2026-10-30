; AP/02 XIP example body for B0:9020. Uses only public RAM console/HOLD calls.
; No application RAM/ZP, flash, SRAM, clock or I/O configuration is modified.
        MODULE BASE1_APP_DEMO
        INCLUDE "str8n-v2-public.inc"
        CODE
APP_START:
        SEI
        CLD
        LDX #0
APP_PRINT:
        LDA APP_TEXT,X
        BEQ APP_WAIT
        PHX
        JSR STR8V2_RAM_PUTC
        PLX
        INX
        BRA APP_PRINT
APP_WAIT:
        JSR STR8V2_RAM_GETC
        CMP #'Q'
        BEQ APP_RETURN
        CMP #'q'
        BEQ APP_RETURN
        CMP #'?'
        BEQ APP_START
        BRA APP_WAIT
APP_RETURN:
        JMP STR8V2_RAM_HOLD
APP_TEXT: DB "APPDEMO / BASE1 PR05",13,10,"? help; Q returns MON",13,10,"APP> ",0
APP_END:
        ENDMOD
        END
