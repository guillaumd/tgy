
;-- Commutation drive macros ---------------------------------------------

.if HIGH_SIDE_PWM
	.macro COMMUTATE_A_on
		AnFET_on
	.endmacro
	.macro COMMUTATE_A_off
		AnFET_off
	.endmacro
	.macro COMMUTATE_B_on
		BnFET_on
	.endmacro
	.macro COMMUTATE_B_off
		BnFET_off
	.endmacro
	.macro COMMUTATE_C_on
		CnFET_on
	.endmacro
	.macro COMMUTATE_C_off
		CnFET_off
	.endmacro
.else
	.macro COMMUTATE_A_on
		ApFET_on
	.endmacro
	.macro COMMUTATE_A_off
		ApFET_off
	.endmacro
	.macro COMMUTATE_B_on
		BpFET_on
	.endmacro
	.macro COMMUTATE_B_off
		BpFET_off
	.endmacro
	.macro COMMUTATE_C_on
		CpFET_on
	.endmacro
	.macro COMMUTATE_C_off
		CpFET_off
	.endmacro
.endif

