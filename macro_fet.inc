;-- FET driving macros ---------------------------------------------------
; Careful: "if" conditions split over multiple lines (with backslashes)
; work with arva, but avrasm2.exe silently produces wrong results.

.if !defined(HIGH_SIDE_PWM)
.equ HIGH_SIDE_PWM = 0
.endif

.if defined(AnFET)
; Traditional direct high and low side drive, inverted if INIT_Px is set.
; Dead-time insertion is supported for COMP_PWM.

	.equ CPWM_SOFT = COMP_PWM

	.macro FET_on
		.if (INIT_PB & ((@0 == PORTB) << @1)) | (INIT_PC & ((@0 == PORTC) << @1)) | (INIT_PD & ((@0 == PORTD) << @1))
		cbi	@0, @1
		.else
		sbi	@0, @1
		.endif
	.endmacro

	.macro FET_off
		.if (INIT_PB & ((@0 == PORTB) << @1)) | (INIT_PC & ((@0 == PORTC) << @1)) | (INIT_PD & ((@0 == PORTD) << @1))
		sbi	@0, @1
		.else
		cbi	@0, @1
		.endif
	.endmacro

	.macro AnFET_on
		FET_on	AnFET_port, AnFET
	.endmacro
	.macro AnFET_off
		FET_off	AnFET_port, AnFET
	.endmacro
	.macro ApFET_on
		FET_on	ApFET_port, ApFET
	.endmacro
	.macro ApFET_off
		FET_off	ApFET_port, ApFET
	.endmacro
	.macro BnFET_on
		FET_on	BnFET_port, BnFET
	.endmacro
	.macro BnFET_off
		FET_off	BnFET_port, BnFET
	.endmacro
	.macro BpFET_on
		FET_on	BpFET_port, BpFET
	.endmacro
	.macro BpFET_off
		FET_off	BpFET_port, BpFET
	.endmacro
	.macro CnFET_on
		FET_on	CnFET_port, CnFET
	.endmacro
	.macro CnFET_off
		FET_off	CnFET_port, CnFET
	.endmacro
	.macro CpFET_on
		FET_on	CpFET_port, CpFET
	.endmacro
	.macro CpFET_off
		FET_off	CpFET_port, CpFET
	.endmacro

	.macro PWM_FOCUS_A_on
		.if COMP_PWM
		cpse	temp3, temp4
		PWM_COMP_A_on
		.endif
	.endmacro
	.macro PWM_FOCUS_A_off
		.if COMP_PWM
		in	temp3, PWM_COMP_A_PORT_in
		PWM_COMP_A_off
		in	temp4, PWM_COMP_A_PORT_in
		.endif
	.endmacro
	.macro PWM_FOCUS_B_on
		.if COMP_PWM
		cpse	temp3, temp4
		PWM_COMP_B_on
		.endif
	.endmacro
	.macro PWM_FOCUS_B_off
		.if COMP_PWM
		in	temp3, PWM_COMP_B_PORT_in
		PWM_COMP_B_off
		in	temp4, PWM_COMP_B_PORT_in
		.endif
	.endmacro
	.macro PWM_FOCUS_C_on
		.if COMP_PWM
		cpse	temp3, temp4
		PWM_COMP_C_on
		.endif
	.endmacro
	.macro PWM_FOCUS_C_off
		.if COMP_PWM
		in	temp3, PWM_COMP_C_PORT_in
		PWM_COMP_C_off
		in	temp4, PWM_COMP_C_PORT_in
		.endif
	.endmacro

	; For PWM state mirroring in commutation routines
	.if HIGH_SIDE_PWM
		.equ	PWM_A_PORT_in = ApFET_port
		.equ	PWM_B_PORT_in = BpFET_port
		.equ	PWM_C_PORT_in = CpFET_port
		.equ	PWM_COMP_A_PORT_in = AnFET_port
		.equ	PWM_COMP_B_PORT_in = BnFET_port
		.equ	PWM_COMP_C_PORT_in = CnFET_port
	.else
		.equ	PWM_A_PORT_in = AnFET_port
		.equ	PWM_B_PORT_in = BnFET_port
		.equ	PWM_C_PORT_in = CnFET_port
		.equ	PWM_COMP_A_PORT_in = ApFET_port
		.equ	PWM_COMP_B_PORT_in = BpFET_port
		.equ	PWM_COMP_C_PORT_in = CpFET_port
	.endif

	.macro PWM_ALL_off
		.if HIGH_SIDE_PWM
		all_pFETs_off @0
		.else
		all_nFETs_off @0
		.endif
	.endmacro

	.macro all_pFETs_off
	.if ApFET_port != BpFET_port || ApFET_port != CpFET_port
		ApFET_off
		BpFET_off
		CpFET_off
	.else
		in	@0, ApFET_port
		.if (INIT_PB & ((ApFET_port == PORTB) << ApFET)) | (INIT_PC & ((ApFET_port == PORTC) << ApFET)) | (INIT_PD & ((ApFET_port == PORTD) << ApFET))
		sbr	@0, (1<<ApFET)+(1<<BpFET)+(1<<CpFET)
		.else
		cbr	@0, (1<<ApFET)+(1<<BpFET)+(1<<CpFET)
		.endif
		out	ApFET_port, @0
	.endif
	.endmacro

	.macro all_nFETs_off
	.if AnFET_port != BnFET_port || AnFET_port != CnFET_port
		AnFET_off
		BnFET_off
		CnFET_off
	.else
		in	@0, AnFET_port
		.if (INIT_PB & ((AnFET_port == PORTB) << AnFET)) | (INIT_PC & ((AnFET_port == PORTC) << AnFET)) | (INIT_PD & ((AnFET_port == PORTD) << AnFET))
		sbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
		.else
		cbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
		.endif
		out	AnFET_port, @0
	.endif
	.endmacro

	.macro nFET_brake
	.if AnFET_port != BnFET_port || AnFET_port != CnFET_port
		AnFET_on
		BnFET_on
		CnFET_on
	.else
		in	@0, AnFET_port
		.if (INIT_PB & ((AnFET_port == PORTB) << AnFET)) | (INIT_PC & ((AnFET_port == PORTC) << AnFET)) | (INIT_PD & ((AnFET_port == PORTD) << AnFET))
		cbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
		.else
		sbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
		.endif
		out	AnFET_port, @0
	.endif
	.endmacro

.elif defined(ENABLE_ALL)
; Three logic level PWM/ENABLE-style driver, with diode emulation mode or
; off state at the middle level on the PWM pin. This is accomplished by
; setting a pull-up rather than drive high. With this method, every FET
; toggle can be a single I/O instruction, rather than having to select
; high or low in advance to toggling enable. The following macros are used:
;
; XnFET_on  -> cbi PWM_X_PORT, PWM_X (drain through ext pull-down)
; XnFET_off -> sbi PWM_X_PORT, PWM_X (pull-up pin with ext pull-down)
; XpFET_on  -> sbi PWM_X_DDR, PWM_X (drive-up pin)
; XpFET_off -> cbi PWM_X_DDR, PWM_X (pull-up pin with ext pull-down)
;
; COMP_PWM on these is done in hardware rather than software, so we can
; just toggle the PORT value after PWM_FOCUS sets DDR (output mode).
; This results in the following macro arrangement:
;
; TRI	CPWM	HIGH_SIDE_PWM	: PWM ON	PWM OFF		PWM_X_PORT_in
; 0	0	0		: XnFET_on	XnFET_off	XnFET_port
; 0	0	1		: XpFET_on	XpFET_off	XpFET_port
; 0	1	0		: XnFET_on	XnFET_off	XnFET_port
; 0	1	1		: XpFET_on	XpFET_off	XpFET_port
; 1	0	0		: XnFET_on	XnFET_off	PWM_X_PORT
; 1	0	1		: XpFET_on	XpFET_off	PWM_X_DDR
; 1	1	0		: XnFET_on	XnFET_off	PWM_X_PORT
; 1	1	1		: XnFET_off	XnFET_on	PWM_X_PORT
;
; For the last case, PWM_X_off actually turns low side on which isn't how
; we want to leave the phase after commutating. PWM_X_clear will take care
; of this.
;
; We leave ENABLE high once initialized as some drivers will actually
; shut down rather than just using the input as a logic gate.
;
; We prefer HIGH_SIDE_PWM as diode emulation mode in these drivers
; typically allows active freewheeling only in this orientation.

	.equ CPWM_SOFT = 0

	.macro AnFET_on
		cbi	PWM_A_PORT, PWM_A
	.endmacro
	.macro AnFET_off
		sbi	PWM_A_PORT, PWM_A
	.endmacro
	.macro ApFET_on
		sbi	PWM_A_DDR, PWM_A
	.endmacro
	.macro ApFET_off
		cbi	PWM_A_DDR, PWM_A
	.endmacro
	.macro BnFET_on
		cbi	PWM_B_PORT, PWM_B
	.endmacro
	.macro BnFET_off
		sbi	PWM_B_PORT, PWM_B
	.endmacro
	.macro BpFET_on
		sbi	PWM_B_DDR, PWM_B
	.endmacro
	.macro BpFET_off
		cbi	PWM_B_DDR, PWM_B
	.endmacro
	.macro CnFET_on
		cbi	PWM_C_PORT, PWM_C
	.endmacro
	.macro CnFET_off
		sbi	PWM_C_PORT, PWM_C
	.endmacro
	.macro CpFET_on
		sbi	PWM_C_DDR, PWM_C
	.endmacro
	.macro CpFET_off
		cbi	PWM_C_DDR, PWM_C
	.endmacro

	.macro PWM_FOCUS_A_on
		.if COMP_PWM
		sbrc	flags1, POWER_ON
		ApFET_on
		.endif
	.endmacro
	.macro PWM_FOCUS_A_off
		.if COMP_PWM
		ApFET_off
		.endif
	.endmacro

	.macro PWM_FOCUS_B_on
		.if COMP_PWM
		sbrc	flags1, POWER_ON
		BpFET_on
		.endif
	.endmacro
	.macro PWM_FOCUS_B_off
		.if COMP_PWM
		BpFET_off
		.endif
	.endmacro

	.macro PWM_FOCUS_C_on
		.if COMP_PWM
		sbrc	flags1, POWER_ON
		CpFET_on
		.endif
	.endmacro
	.macro PWM_FOCUS_C_off
		.if COMP_PWM
		CpFET_off
		.endif
	.endmacro

	; For PWM state mirroring in commutation routines
	.if COMP_PWM || !HIGH_SIDE_PWM
		.equ	PWM_A_PORT_in = PWM_A_PORT
		.equ	PWM_B_PORT_in = PWM_B_PORT
		.equ	PWM_C_PORT_in = PWM_C_PORT
	.else
		.equ	PWM_A_PORT_in = PWM_A_DDR
		.equ	PWM_B_PORT_in = PWM_B_DDR
		.equ	PWM_C_PORT_in = PWM_C_DDR
	.endif

	.macro PWM_ALL_off
		all_nFETs_off @0
	.endmacro

	.macro all_pFETs_off
		.if PWM_A_DDR != PWM_B_DDR || PWM_A_DDR != PWM_C_DDR
			ApFET_off
			BpFET_off
			CpFET_off
		.else
			in	@0, PWM_A_DDR
			cbr	@0, (1<<PWM_A)+(1<<PWM_B)+(1<<PWM_C)
			out	PWM_A_DDR, @0
		.endif
	.endmacro

	.macro all_nFETs_off
		.if PWM_A_PORT != PWM_B_PORT || PWM_A_PORT != PWM_C_PORT
			AnFET_off
			BnFET_off
			CnFET_off
		.else
			in	@0, PWM_A_PORT
			sbr	@0, (1<<PWM_A)+(1<<PWM_B)+(1<<PWM_C)
			out	PWM_A_PORT, @0
		.endif
	.endmacro

	.macro nFET_brake
		.if PWM_A_PORT != PWM_B_PORT || PWM_A_PORT != PWM_C_PORT
			AnFET_on
			BnFET_on
			CnFET_on
		.else
			in	@0, PWM_A_PORT
			cbr	@0, (1<<PWM_A)+(1<<PWM_B)+(1<<PWM_C)
			out	PWM_A_PORT, @0
		.endif
	.endmacro

.endif
