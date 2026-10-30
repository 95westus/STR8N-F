; Explicit EDU Rev D / 23LCV1024 profile only. RDMR(05) and READ(03), never
; WRITE(02), WRMR(01), format, repair, resize or probe-by-writing.
W_EDU_CMD:
        JSR W_SKIP
        BEQ W_EDU_SHOW
        CMP #'O'
        BNE W_UNHANDLED
        INX
        LDA W_LINE,X
        CMP #'N'
        BEQ W_EDU_ON
        CMP #'F'
        BNE W_UNHANDLED
        INX
        LDA W_LINE,X
        CMP #'F'
        BNE W_UNHANDLED
        INX
        JSR W_END_ARGS
        BCC W_UNHANDLED
        STZ W_EDU
        BRA W_EDU_SHOW
W_EDU_ON:
        INX
        JSR W_END_ARGS
        BCC W_UNHANDLED
        LDA #1
        STA W_EDU
W_EDU_SHOW:
        LDX #<W_EDU_OFF_TEXT
        LDY #>W_EDU_OFF_TEXT
        LDA W_EDU
        BEQ W_EDU_PRINT
        LDX #<W_EDU_ON_TEXT
        LDY #>W_EDU_ON_TEXT
W_EDU_PRINT:
        JSR W_PUTS
        JMP W_HANDLED
W_SRAM_CMD:
        JSR W_SKIP
        BEQ W_STORAGE_STATUS
        LDY #0
W_PREP_MATCH:
        LDA W_LINE,X
        CMP W_PREP_WORD,Y
        BNE W_UNHANDLED
        INX
        INY
        CPY #4
        BCC W_PREP_MATCH
        JSR W_END_ARGS
        BCC W_UNHANDLED
        LDA W_EDU
        BEQ W_EDU_REQUIRED
        JSR W_SPI_GUARD
        BCC W_PIN_BUSY
        ; Deliberately acknowledge only disabled CB flags, with idle pins.
        ; There is no ORB read in the ordinary guard/refusal path.
        LDA W_IFR
        AND #$18
        BEQ W_PREP_DONE
        LDA W_ORB
        LDA W_IFR
        AND #$18
        BNE W_PIN_BUSY
W_PREP_DONE:
        LDX #<W_PREP_TEXT
        LDY #>W_PREP_TEXT
        JSR W_PUTS
        JMP W_HANDLED
W_WORK_CMD:
        JSR W_END_ARGS
        BCC W_UNHANDLED
W_STORAGE_STATUS:
        LDA W_EDU
        BEQ W_EDU_REQUIRED
        STZ W_A0
        STZ W_A1
        STZ W_A2
        STZ W_FALLBACK
        JSR W_SPI_READ64
        BCC W_STORAGE_ERROR
        LDA W_LAYOUT+63
        CMP #$A5
        BEQ W_VALIDATE_LAYOUT
        INC W_FALLBACK
        LDA #$40
        STA W_A0
        LDA #2
        STA W_A1
        STZ W_A2
        JSR W_SPI_READ64
        BCC W_STORAGE_ERROR
        LDA W_LAYOUT+63
        CMP #$A5
        BNE W_LAYOUT_INVALID
W_VALIDATE_LAYOUT:
        LDY #3
W_LAYOUT_MAGIC:
        LDA W_LAYOUT,Y
        CMP W_LAYOUT_EXPECTED,Y
        BEQ W_LAYOUT_MAGIC_NEXT
        CPY #2
        BNE W_LAYOUT_INVALID
        CMP #1
        BNE W_LAYOUT_INVALID
W_LAYOUT_MAGIC_NEXT:
        DEY
        BPL W_LAYOUT_MAGIC
        LDA W_LAYOUT+4
        CMP #8
        BNE W_LAYOUT_INVALID
        LDA W_LAYOUT+7
        ORA W_LAYOUT+62
        BNE W_LAYOUT_INVALID
        LDY #59
W_LAYOUT_RESERVED:
        LDA W_LAYOUT,Y
        BNE W_LAYOUT_INVALID
        DEY
        CPY #11
        BNE W_LAYOUT_RESERVED
        JSR W_CRC_START
        LDY #0
W_LAYOUT_CRC:
        LDA W_LAYOUT,Y
        JSR W_CRC_BYTE
        INY
        CPY #62
        BCC W_LAYOUT_CRC
        LDA W_CRC
        ORA W_CRC+1
        BNE W_LAYOUT_INVALID
        LDA W_LAYOUT+8
        ORA W_LAYOUT+9
        ORA W_LAYOUT+10
        ORA W_LAYOUT+11
        STA W_TMP
        LDA W_LAYOUT+2
        CMP #1
        BNE W_LAYOUT_MODERN
        ; SS1: primary only, zero generation, fixed 64KiB PROGRAM boundary.
        LDA W_TMP
        ORA W_FALLBACK
        ORA W_LAYOUT+5
        BNE W_LAYOUT_INVALID
        LDA W_LAYOUT+6
        CMP #1
        BNE W_LAYOUT_INVALID
        BRA W_LAYOUT_BOUNDARY
W_LAYOUT_MODERN:
        LDA W_TMP
        BEQ W_LAYOUT_INVALID
W_LAYOUT_BOUNDARY:
        LDA W_LAYOUT+5
        AND #$3F
        BNE W_LAYOUT_INVALID
        LDA W_LAYOUT+6
        BEQ W_LAYOUT_SMALL
        CMP #1
        BNE W_LAYOUT_INVALID
        LDA W_LAYOUT+5
        BNE W_LAYOUT_INVALID
        LDA #4
        BRA W_LAYOUT_UNITS
W_LAYOUT_SMALL:
        LDA W_LAYOUT+5
        BEQ W_LAYOUT_INVALID
        LSR A
        LSR A
        LSR A
        LSR A
        LSR A
        LSR A
W_LAYOUT_UNITS:
        DEC A
        STA W_UNIT
        LDA W_LAYOUT+5
        STA W_BOUNDARY
        LDA W_LAYOUT+6
        STA W_BOUNDARY+1
        LDA W_FALLBACK
        BEQ W_LAYOUT_PRINT
        LDX #<W_FALLBACK_TEXT
        LDY #>W_FALLBACK_TEXT
        JSR W_PUTS
W_LAYOUT_PRINT:
        LDA W_LAYOUT+2
        CMP #1
        BNE W_LAYOUT_CAPACITY
        LDX #<W_LAYOUT_V1_TEXT
        LDY #>W_LAYOUT_V1_TEXT
        JSR W_PUTS
W_LAYOUT_CAPACITY:
        LDX #<W_PROGRAM_TEXT
        LDY #>W_PROGRAM_TEXT
        JSR W_PUTS
        LDX W_UNIT
        LDA W_CAP_LO,X
        LDY W_CAP_HI,X
        TAX
        JSR W_PUTS
        LDX #<W_WORK_TEXT
        LDY #>W_WORK_TEXT
        JSR W_PUTS
        LDX #<W_WORK_GUARD_TEXT
        LDY #>W_WORK_GUARD_TEXT
        JSR W_PUTS
        JMP W_HANDLED
W_EDU_REQUIRED:
        LDX #<W_EDU_REQUIRED_TEXT
        LDY #>W_EDU_REQUIRED_TEXT
        JMP W_RECORD_ERROR
W_PIN_BUSY:
        LDX #<W_PIN_BUSY_TEXT
        LDY #>W_PIN_BUSY_TEXT
        JMP W_RECORD_ERROR
W_LAYOUT_INVALID:
        LDX #<W_LAYOUT_INVALID_TEXT
        LDY #>W_LAYOUT_INVALID_TEXT
        JMP W_RECORD_ERROR
W_STORAGE_ERROR:
        CMP #1
        BEQ W_PIN_BUSY
        LDX #<W_SRAM_UNAVAILABLE_TEXT
        LDY #>W_SRAM_UNAVAILABLE_TEXT
        JMP W_RECORD_ERROR
W_SPI_GUARD:
        LDA W_IER
        AND #$18
        BNE W_SPI_BUSY
        LDA W_PCR
        AND #$F0
        BNE W_SPI_BUSY
        LDA W_ACR
        AND #$1E
        BNE W_SPI_BUSY
        LDA W_DDR
        AND #$2F
        BNE W_SPI_BUSY
        SEC
        RTS
W_SPI_BUSY:
        LDA #1
        CLC
        RTS
W_SPI_READ64:
        JSR W_SPI_GUARD
        BCC W_SPI_RETURN
        LDA W_IFR
        AND #$18
        BNE W_SPI_BUSY
        ; Requested addresses are internal fixed layout pages, both below 20000.
        LDA W_DDR
        STA W_ODDR
        LDA W_ORB
        STA W_OORB
        AND #$FC
        ORA #$0C
        STA W_PORT
        STA W_ORB
        LDA W_ODDR
        AND #$DF
        ORA #$0F
        STA W_DDR
        LDA #5
        JSR W_SPI_COMMAND
        LDA #$FF
        JSR W_SPI_BYTE
        STA W_TMP
        JSR W_SPI_DESELECT
        LDA W_TMP
        BEQ W_SPI_MODE_OK
        CMP #$40
        BEQ W_SPI_MODE_OK
        CMP #$80
        BNE W_SPI_NO_DEVICE
W_SPI_MODE_OK:
        STZ W_SPI_LEFT
W_SPI_READ_NEXT:
        LDA #3
        JSR W_SPI_COMMAND
        LDA W_A2
        JSR W_SPI_BYTE
        LDA W_A1
        JSR W_SPI_BYTE
        LDA W_A0
        JSR W_SPI_BYTE
        LDA #$FF
        JSR W_SPI_BYTE
        LDY W_SPI_LEFT
        STA W_LAYOUT,Y
        JSR W_SPI_DESELECT
        INC W_A0
        BNE W_SPI_ADVANCE
        INC W_A1
        BNE W_SPI_ADVANCE
        INC W_A2
W_SPI_ADVANCE:
        INC W_SPI_LEFT
        LDA W_SPI_LEFT
        CMP #64
        BCC W_SPI_READ_NEXT
        JSR W_SPI_RESTORE
        LDA #0
        SEC
W_SPI_RETURN:
        RTS
W_SPI_NO_DEVICE:
        JSR W_SPI_RESTORE
        LDA #2
        CLC
        RTS
W_SPI_RESTORE:
        JSR W_SPI_DESELECT
        LDA W_ODDR
        STA W_DDR
        LDA W_OORB
        STA W_ORB
        RTS
W_SPI_COMMAND:
        PHA
        LDA W_PORT
        AND #$FB
        STA W_PORT
        STA W_ORB
        PLA
        JMP W_SPI_BYTE
W_SPI_DESELECT:
        LDA W_PORT
        ORA #$0C
        STA W_PORT
        STA W_ORB
        RTS
W_SPI_BYTE:
        STA W_TX
        LDX #8
W_SPI_BIT:
        LDA #2
        TRB W_PORT
        ASL W_TX
        BCC W_SPI_ZERO
        TSB W_PORT
W_SPI_ZERO:
        LDA W_PORT
        STA W_ORB
        INC A
        STA W_ORB
        LDA W_ORB
        ASL A
        ASL A
        ASL A
        ROL W_RX
        LDA W_PORT
        STA W_ORB
        DEX
        BNE W_SPI_BIT
        LDA W_RX
        RTS
W_EDU_WORD: DB "EDU",0
W_SRAM_WORD: DB "SRAM",0
W_WORK_WORD: DB "WORK",0
W_PREP_WORD: DB "PREP"
W_LAYOUT_EXPECTED: DB "SS",2,8
W_EDU_OFF_TEXT: DB "EDU OFF (session; no bus access)",13,10,0
W_EDU_ON_TEXT: DB "EDU ON (Rev D profile; not presence proof)",13,10,0
W_EDU_REQUIRED_TEXT: DB "EDU OFF; use EDU ON (Rev D)",13,10,0
W_PREP_TEXT: DB "Disabled CB flags acknowledged; no SPI clocks",13,10,0
W_PIN_BUSY_TEXT: DB "SSRAM: pins/CB flags busy; no SPI transaction",13,10,0
W_LAYOUT_INVALID_TEXT: DB "SSRAM: no valid SS1/SS2 layout; no repair",13,10,0
W_LAYOUT_V1_TEXT: DB "SSRAM: legacy SS1 layout (read only)",13,10,0
W_SRAM_UNAVAILABLE_TEXT: DB "SSRAM: unavailable (mode response rejected)",13,10,0
W_FALLBACK_TEXT: DB "SSRAM: fallback SS2; review primary; read only",13,10,0
W_PROGRAM_TEXT: DB "SSRAM: PROGRAM payload ",0
W_WORK_TEXT: DB " bytes",13,10,0
W_WORK_GUARD_TEXT: DB "WORKSPACE unmounted; messages/source writes disabled",13,10,0
W_CAP16: DB "14336 bytes; WORKSPACE 114656",0
W_CAP32: DB "30720 bytes; WORKSPACE 98272",0
W_CAP48: DB "47104 bytes; WORKSPACE 81888",0
W_CAP64: DB "63488 bytes; WORKSPACE 65504",0
W_CAP_LO: DB <W_CAP16,<W_CAP32,<W_CAP48,<W_CAP64
W_CAP_HI: DB >W_CAP16,>W_CAP32,>W_CAP48,>W_CAP64
