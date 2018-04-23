; Print.s
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
		
; Error message (null-terminated string)
ErrorString     DCB     "*.***", 0

    THUMB

	; bypass 8 byte alignment on the stack
	; allows an odd number of register pushes and pops
	PRESERVE8


;-----------------------extractChar------------------------------------------
; Extract a single character from the ASCII representation of an integer, and
; save onto a stack with stack pointer R1.
; Inputs: 
;   R0 - 32-bit unsigned number
;   R1 - stack pointer to allocated stack
; Output: R0 / 10
; Modifies: R1 (stack pointer)
;----------------------------------------------------------------------------
extractChar
    PUSH {R2-R4, LR}

    MOV R3, #10
    ; R0/10 -> R4
    MOV R4, R0
    UDIV R4, R3
    ; R4*10 -> R2
    MOV R2, R4
    MUL R2, R3
    ; R0 - (R0/10*10) -> R0 (R0 = R0 % 10)
    SUB R0, R0, R2
    
    ; Push ASCII character to stack R1
    ADD R0, R0, #0x30
    SUB R1, #1
    STRB R0, [R1]

    ; Return
    MOV R0, R4
    POP {R2-R4, LR}
    BX LR


;-----------------------displayPrint-----------------------------------------
; Display a null-terminated string on the display
; Input: R0 - pointer to string
; Output: none
;----------------------------------------------------------------------------
displayPrint
    PUSH {R4, LR}
    MOV R4, R0
displayPrintLoop
    ; Pop value off the stack
    LDRB R0, [R4]
    ADD R4, R4, #1
    ; Exit if null termination is reached
    CMP R0, #0
    BEQ displayPrintExit
    ; Display character
    BL ST7735_OutChar
    B displayPrintLoop

displayPrintExit

    POP {R4, LR}
    BX LR
  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11

; Local variable binding phase
outDec_CurrentValue EQU     -16     ; Storage for the current value on the stack because the lab said so
	
LCD_OutDec

    PUSH {LR, R1, R2, R11}

    ; Allocate 20 bytes of data on the stack
    ; R1 contains the secondary stack pointer; R11 contains the frame pointer
    MOV R11, SP
    MOV R1, SP
    SUB SP, #20
    STR R0, [R11, #outDec_CurrentValue]

    ; Add null termination to string buffer
    SUB R1, #1
    MOV R2, #0x00
    STR R2, [R1]

    ; Extract characters from R0 until R0=0.
LCD_OutDec_Loop
    LDR R0, [R11, #outDec_CurrentValue]
    BL extractChar
    STR R0, [R11, #outDec_CurrentValue]
    CMP R0, #0
    BNE LCD_OutDec_Loop
    
    ; Print the resulting string
    MOV R0, R1
    BL displayPrint
    
    ; Restore SP, other registers
    ADD SP, #20
    POP{LR, R1, R2, R11}	

	BX  LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *


; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11

; Local variable binding phase
outFix_CurrentValue EQU     -16     ; Storage for the current value on the stack because the lab said so

LCD_OutFix
    PUSH {LR, R1-R4, R11}

    ; Allocate 20 bytes of data on the stack
    ; R1 contains the secondary stack pointer; R11 contains the frame pointer
    MOV R11, SP
    MOV R1, SP
    SUB SP, #20
    STR R0, [R11, #outFix_CurrentValue]

    ; Add null termination to string buffer
    SUB R1, #1
    MOV R2, #0x00
    STR R2, [R1]
    
    ; Ensure that R0<9999
    MOV R2, #9999
    CMP R0, R2
    ITT HI
    LDRHI R1, =ErrorString
    BHI LCD_OutFix_Print
    
    ; Extract 4 characters from R0
    MOV R4, #0x00
	
LCD_OutFix_Loop
    LDR R0, [R11, #outFix_CurrentValue]
    BL extractChar
    STR R0, [R11, #outFix_CurrentValue]
    ; Add decimal point
    CMP R4, #0x02
    ITTT EQ
    MOVEQ R3, #0x2E
    SUBEQ R1, #1
    STRBEQ R3, [R1]
    ; Check to see if enough characters have been extracted
    ADD R4, R4, #1
    CMP R4, #0x04
    BNE LCD_OutFix_Loop
    
    ; Print the resulting string
LCD_OutFix_Print
    MOV R0, R1
    BL displayPrint
    
    ; Restore SP, other registers
    ADD SP, #20
    POP{LR, R1-R4, R11}
	BX   LR
 
	ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

	ALIGN                           ; make sure the end of this section is aligned
	END                             ; end of file
