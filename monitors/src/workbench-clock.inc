; New BASE1 CLOCK page. Only bounded RTC reads; legacy administration is not
; called until its provider/flash bookkeeping has been ported and qualified.
WC_MAINT:
        JSR W_END_ARGS
        BCC W_UNHANDLED
        JMP W_SHELL
WC_COMMAND:
        JSR W_END_ARGS
        BCC W_UNHANDLED
        LDX #<WC_UI_TITLE
        LDY #>WC_UI_TITLE
        JSR W_PUTS
WC_REFRESH:
        JSR WC_SAMPLE
        STA WC_RESULT
        BEQ WC_SHOW
        LDX #<WC_ERROR_TEXT
        LDY #>WC_ERROR_TEXT
        JSR W_PUTS
        LDA WC_RESULT
        JSR STR8V2_RAM_HEX_OUT
        JSR STR8V2_RAM_NEWLINE
WC_SHOW:
        JSR WC_DISPLAY
WC_MENU:
        LDX #<WC_PROMPT
        LDY #>WC_PROMPT
        JSR W_PUTS
        JSR W_READ_LINE
        BCC WC_MENU
        LDX #<WC_Q_WORD
        LDY #>WC_Q_WORD
        JSR W_MATCH
        BCS WC_QUIT
        LDX #<WC_R_WORD
        LDY #>WC_R_WORD
        JSR W_MATCH
        BCS WC_UI_READ
        LDX #<WC_TIME_WORD
        LDY #>WC_TIME_WORD
        JSR W_MATCH
        BCS WC_UI_READ
        LDX #<WC_HELP_WORD
        LDY #>WC_HELP_WORD
        JSR W_MATCH
        BCS WC_HELP
        LDX #<WS_HELP_WORD
        LDY #>WS_HELP_WORD
        JSR W_MATCH
        BCS WC_HELP
WC_BAD:
        LDX #<W_SYNTAX_TEXT
        LDY #>W_SYNTAX_TEXT
        JSR W_PUTS
        BRA WC_MENU
WC_UI_READ:
        JSR W_END_ARGS
        BCC WC_BAD
        BRA WC_REFRESH
WC_HELP:
        JSR W_END_ARGS
        BCC WC_BAD
        LDX #<WC_UI_TITLE
        LDY #>WC_UI_TITLE
        JSR W_PUTS
        BRA WC_MENU
WC_QUIT:
        JSR W_END_ARGS
        BCC WC_BAD
        STZ W_RESULT
        JMP W_HANDLED
WC_WORD: DB "CLOCK",0
WC_MAINT_WORD: DB "MAINT",0
WC_FLASH_WORD: DB "FLASH",0
WC_Q_WORD: DB "Q",0
WC_R_WORD: DB "R",0
WC_TIME_WORD: DB "TIME",0
WC_HELP_WORD: DB "?",0
WC_UI_TITLE: DB "CLOCK BASE1 / PR05 - read-only Rev D MCP79411",13,10
        DB "R/TIME refresh; Q return; ? help. Zone unconfigured.",13,10
        DB "* Flags observed; battery health unverified. SET/history planned.",13,10,0
WC_PROMPT: DB "CLOCK> ",0
WC_ERROR_TEXT: DB "RTC read refused/failed $",0
