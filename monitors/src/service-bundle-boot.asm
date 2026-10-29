; Optional B2:8000 entry. A 512-byte prefix includes a one-page RAM loader.
        MODULE SERVICE_BUNDLE
        INCLUDE "workbench-interface.inc"
        INCLUDE "service-interface.inc"
        CODE
SBB_START:
        JMP SBB_BOOT
        DB "WF",WB_FORMAT,WB_PAGES,"PR05"
        DB "SERVICE_GENERATION_BYTES"
SBB_BOOT:
        SEI
        CLD
        LDX #$FF
        TXS
        LDA #1
        STA SB_ENTRY_MODE
        LDA #2
        STA SB_CLIENT_FLOOR
        LDX #0
SBB_COPY:
        LDA $8100,X
        STA SB_LOAD_RAM,X
        INX
        BNE SBB_COPY
        JMP SB_LOAD_RAM
SBB_END:
        ENDMOD
        END
