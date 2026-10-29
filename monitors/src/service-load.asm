; RAM bank-safe loader for the explicitly requested flash workbench.
; Linked at7000, below the frozen 7800 worker. Never writes flash or SPI SRAM.
        MODULE SERVICE_LOAD
        INCLUDE "str8n-v2-public.inc"
        INCLUDE "workbench-interface.inc"
        INCLUDE "service-interface.inc"
        INCLUDE "service-foundation.inc"
SL_PTR EQU $E0
SL_COPY EQU $E6
SL_CRC EQU $69F8
        CODE
SL_START:
        SEI
        CLD
        LDX #3
SL_RA_CHECK:
        LDA STR8V2_RAM_SIGNATURE,X
        CMP SL_RA,X
        BNE SL_LOCK
        DEX
        BPL SL_RA_CHECK
        LDA #3
        JSR SB_F_SELECT
        LDA #$F0
        LDX #16
        JSR SL_CRC_PAGES
        LDA SL_CRC
        CMP #SB_F_CRC_LO
        BNE SL_LOCK
        LDA SL_CRC+1
        CMP #SB_F_CRC_HI
        BNE SL_LOCK
        LDA #2
        JSR SB_F_SELECT
        LDX #7
SL_BUNDLE_CHECK:
        LDA $8003,X
        CMP SL_BUNDLE,X
        BNE SL_FAIL_BANK
        DEX
        BPL SL_BUNDLE_CHECK
        STZ SL_PTR
        STZ SL_COPY
        LDA #>SB_MODULE_SOURCE
        STA SL_PTR+1
        LDA #>WB_ORIGIN
        STA SL_COPY+1
        LDX #WB_PAGES
        LDY #0
SL_COPY_BYTE:
        LDA (SL_PTR),Y
        STA (SL_COPY),Y
        INY
        BNE SL_COPY_BYTE
        INC SL_PTR+1
        INC SL_COPY+1
        DEX
        BNE SL_COPY_BYTE
        LDA #3
        JSR SB_F_SELECT
        LDX #7
SL_MODULE_CHECK:
        LDA WB_ORIGIN,X
        CMP SL_MODULE,X
        BNE SL_FAIL
        DEX
        BPL SL_MODULE_CHECK
        LDA #>WB_ORIGIN
        LDX #WB_PAGES
        JSR SL_CRC_PAGES
        LDA SL_CRC
        ORA SL_CRC+1
        BNE SL_FAIL
        JSR WB_INIT
        LDA SB_ENTRY_MODE
        BNE SL_BOOT
        SEC
        RTS
SL_BOOT:
        JMP WB_SHELL
SL_FAIL_BANK:
        LDA #3
        JSR SB_F_SELECT
SL_FAIL:
        LDA SB_ENTRY_MODE
        BNE SL_RECOVERY
        CLC
        RTS
SL_RECOVERY:
        JMP SB_F_RECOVERY
SL_LOCK:
        BRA SL_LOCK
SL_CRC_PAGES:
        STZ SL_PTR
        STA SL_PTR+1
        LDA #$FF
        STA SL_CRC
        STA SL_CRC+1
        LDY #0
SL_CRC_BYTE:
        LDA (SL_PTR),Y
        EOR SL_CRC+1
        STA SL_CRC+1
        PHY
        LDY #8
SL_CRC_BIT:
        ASL SL_CRC
        ROL SL_CRC+1
        BCC SL_CRC_NEXT
        LDA SL_CRC
        EOR #$21
        STA SL_CRC
        LDA SL_CRC+1
        EOR #$10
        STA SL_CRC+1
SL_CRC_NEXT:
        DEY
        BNE SL_CRC_BIT
        PLY
        INY
        BNE SL_CRC_BYTE
        INC SL_PTR+1
        DEX
        BNE SL_CRC_BYTE
        RTS
SL_RA: DB "RA",1,13
SL_BUNDLE: DB "WF",WB_FORMAT,WB_PAGES,"PR05"
SL_MODULE: DB "MW",WB_FORMAT,WB_PAGES,"PR05"
SL_END:
        ENDMOD
        END
