; Qualification-only SRAM reader/restorer. No flash, layout or WORKSPACE writes.
; W accepts exactly64 bytes with CRC over bank/address/data, then readback.
; The compiled allowlist names exact backed-up PROGRAM blocks; R is read-only.
        MODULE SRAM_BENCH
        INCLUDE "str8n-v2-public.inc"
        INCLUDE "workbench-layout.inc"
        INCLUDE "program-layout.inc"
        INCLUDE "sram-bench-params.inc"
Q_PTR EQU $E0
Q_CRC EQU $3200
Q_COUNT EQU $3202
Q_TEMP EQU $3204
Q_COMMAND EQU $3205
Q_INDEX EQU $3206
Q_BANK EQU $3207
Q_ADDR EQU $3208
Q_EXPECT EQU $320A
Q_LAST EQU $320C
        CODE
Q_START:
        SEI
        CLD
        STZ Q_PTR
        LDA #2
        STA Q_PTR+1
        LDA #<(Q_END-Q_START)
        STA Q_COUNT
        LDA #>(Q_END-Q_START)
        STA Q_COUNT+1
        JSR Q_RANGE_CRC
        LDA Q_CRC
        ORA Q_CRC+1
        BNE Q_HOLD
        STZ Q_PTR
        LDA #$F0
        STA Q_PTR+1
        STZ Q_COUNT
        LDA #16
        STA Q_COUNT+1
        JSR Q_RANGE_CRC
        LDA Q_CRC
        CMP #BENCH_F_LO
        BNE Q_HOLD
        LDA Q_CRC+1
        CMP #BENCH_F_HI
        BNE Q_HOLD
        STZ Q_PTR
        LDA #$6B
        STA Q_PTR+1
        STZ Q_COUNT
        LDA #13
        STA Q_COUNT+1
        JSR Q_RANGE_CRC
        LDA Q_CRC
        ORA Q_CRC+1
        BNE Q_HOLD
        LDA $77FE
        CMP #BENCH_PV_HI
        BNE Q_HOLD
        LDA $77FF
        CMP #BENCH_PV_LO
        BNE Q_HOLD
Q_PROMPT:
        JSR STR8V2_RAM_RX_RESET
        LDA #'>'
        JSR STR8V2_RAM_PUTC
        LDA #' '
        JSR STR8V2_RAM_PUTC
        JSR STR8V2_RAM_GETC
        STA Q_LAST
        CMP #'Q'
        BEQ Q_HOLD
        CMP #'R'
        BEQ Q_FIELDS
        CMP #'W'
        BNE Q_BAD_INPUT
Q_FIELDS:
        STA Q_COMMAND
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        CMP #2
        BCS Q_BAD_INPUT
        STA Q_BANK
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        STA Q_ADDR+1
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        STA Q_ADDR
        JSR Q_INIT_CRC
        LDA Q_BANK
        JSR Q_CRC_BYTE
        LDA Q_ADDR+1
        JSR Q_CRC_BYTE
        LDA Q_ADDR
        JSR Q_CRC_BYTE
        LDA Q_COMMAND
        CMP #'R'
        BEQ Q_READ
        STZ Q_INDEX
Q_INPUT_DATA:
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        LDX Q_INDEX
        STA $3000,X
        JSR Q_CRC_BYTE
        INC Q_INDEX
        LDA Q_INDEX
        CMP #64
        BCC Q_INPUT_DATA
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        STA Q_EXPECT+1
        JSR Q_HEX_BYTE
        BCC Q_BAD_INPUT
        STA Q_EXPECT
        JSR Q_EOL
        BCC Q_BAD_INPUT
        LDA Q_CRC
        CMP Q_EXPECT
        BNE Q_BAD_FRAME
        LDA Q_CRC+1
        CMP Q_EXPECT+1
        BNE Q_BAD_FRAME
        LDA Q_BANK
        BNE Q_BAD_FRAME
        LDY #0
Q_ALLOWED:
        CPY #BENCH_ALLOW_BYTES
        BCS Q_BAD_FRAME
        LDA BENCH_ALLOW,Y
        CMP Q_ADDR
        BNE Q_ALLOWED_NEXT
        LDA BENCH_ALLOW+1,Y
        CMP Q_ADDR+1
        BEQ Q_WRITE
Q_ALLOWED_NEXT:
        INY
        INY
        BRA Q_ALLOWED
Q_WRITE:
        JSR Q_SET_TRANSFER
        LDA #2
        STA SP_OP
        JSR BENCH_TRANSFER
        BNE Q_ERROR
        JSR Q_SET_TRANSFER
        LDA #$40
        STA SP_PTR
        LDA #1
        STA SP_OP
        JSR BENCH_TRANSFER
        BNE Q_ERROR
        LDX #0
Q_COMPARE:
        LDA $3000,X
        CMP $3040,X
        BNE Q_BAD_FRAME
        INX
        CPX #64
        BCC Q_COMPARE
        LDA #'O'
        JSR STR8V2_RAM_PUTC
        BRA Q_CRC_REPLY
Q_READ:
        JSR Q_EOL
        BCC Q_BAD_INPUT
        JSR Q_SET_TRANSFER
        LDA #1
        STA SP_OP
        JSR BENCH_TRANSFER
        BNE Q_ERROR
        LDA #'D'
        JSR STR8V2_RAM_PUTC
        LDA Q_BANK
        JSR STR8V2_RAM_HEX_OUT
        LDA Q_ADDR+1
        JSR STR8V2_RAM_HEX_OUT
        LDA Q_ADDR
        JSR STR8V2_RAM_HEX_OUT
        LDX #0
Q_READ_DATA:
        LDA $3000,X
        JSR Q_CRC_BYTE
        PHX
        JSR STR8V2_RAM_HEX_OUT
        PLX
        INX
        CPX #64
        BCC Q_READ_DATA
Q_CRC_REPLY:
        LDA Q_CRC+1
        JSR STR8V2_RAM_HEX_OUT
        LDA Q_CRC
        JSR STR8V2_RAM_HEX_OUT
        JSR STR8V2_RAM_NEWLINE
        JMP Q_PROMPT
Q_BAD_INPUT:
        LDA Q_LAST
        CMP #13
        BEQ Q_BAD_FRAME
        CMP #10
        BEQ Q_BAD_FRAME
        JSR STR8V2_RAM_GETC
        STA Q_LAST
        BRA Q_BAD_INPUT
Q_BAD_FRAME:
        LDA #$44
Q_ERROR:
        PHA
        LDA #'E'
        JSR STR8V2_RAM_PUTC
        PLA
        JSR STR8V2_RAM_HEX_OUT
        JSR STR8V2_RAM_NEWLINE
        JMP Q_PROMPT
Q_HOLD:
        JMP STR8V2_RAM_HOLD
Q_SET_TRANSFER:
        LDA Q_BANK
        STA SP_A2
        LDA Q_ADDR
        STA SP_A0
        LDA Q_ADDR+1
        STA SP_A1
        STZ SP_PTR
        LDA #$30
        STA SP_PTR+1
        LDA #64
        STA SP_COUNT
        LDA #BENCH_LIMIT
        STA LIMIT
        RTS
Q_EOL:
        JSR STR8V2_RAM_GETC
        STA Q_LAST
        CMP #' '
        BEQ Q_EOL
        CMP #13
        BEQ Q_EOL_OK
        CMP #10
        BNE Q_EOL_BAD
Q_EOL_OK:
        SEC
        RTS
Q_EOL_BAD:
        CLC
        RTS
Q_HEX_BYTE:
        JSR Q_NIBBLE
        BCC Q_EOL_BAD
        ASL A
        ASL A
        ASL A
        ASL A
        STA Q_TEMP
        JSR Q_NIBBLE
        BCC Q_EOL_BAD
        ORA Q_TEMP
        SEC
        RTS
Q_NIBBLE:
        JSR STR8V2_RAM_GETC
        STA Q_LAST
        CMP #' '
        BEQ Q_NIBBLE
        CMP #'0'
        BCC Q_EOL_BAD
        CMP #'9'+1
        BCC Q_DIGIT
        CMP #'A'
        BCC Q_EOL_BAD
        CMP #'F'+1
        BCS Q_EOL_BAD
        SEC
        SBC #7
Q_DIGIT:
        SEC
        SBC #'0'
        SEC
        RTS
Q_INIT_CRC:
        LDA #$FF
        STA Q_CRC
        STA Q_CRC+1
        RTS
Q_CRC_BYTE:
        PHA
        PHX
        EOR Q_CRC+1
        STA Q_CRC+1
        LDX #8
Q_CRC_BIT:
        ASL Q_CRC
        ROL Q_CRC+1
        BCC Q_CRC_NEXT
        LDA Q_CRC
        EOR #$21
        STA Q_CRC
        LDA Q_CRC+1
        EOR #$10
        STA Q_CRC+1
Q_CRC_NEXT:
        DEX
        BNE Q_CRC_BIT
        PLX
        PLA
        RTS
Q_RANGE_CRC:
        JSR Q_INIT_CRC
Q_RANGE_BYTE:
        LDA (Q_PTR)
        JSR Q_CRC_BYTE
        INC Q_PTR
        BNE Q_RANGE_LEFT
        INC Q_PTR+1
Q_RANGE_LEFT:
        LDA Q_COUNT
        BNE Q_RANGE_LOW
        DEC Q_COUNT+1
Q_RANGE_LOW:
        DEC Q_COUNT
        LDA Q_COUNT
        ORA Q_COUNT+1
        BNE Q_RANGE_BYTE
        RTS
BENCH_ALLOW:
        INCLUDE "sram-bench-allow.inc"
Q_IMAGE_CRC: DW 0
Q_END:
        ENDMOD
        END
