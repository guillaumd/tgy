;-- PWM macros -----------------------------------------------------------

.macro PWM_A_on
	.if !defined(AnFET) && COMP_PWM && HIGH_SIDE_PWM
		AnFET_off
	.elif HIGH_SIDE_PWM
		ApFET_on
	.else
		AnFET_on
	.endif
.endmacro
.macro PWM_A_off
	.if !defined(AnFET) && COMP_PWM && HIGH_SIDE_PWM
		AnFET_on
	.elif HIGH_SIDE_PWM
		ApFET_off
	.else
		AnFET_off
	.endif
.endmacro
.macro PWM_A_clear
		in	temp1, PWM_A_PORT_in
	.if !defined(AnFET) && COMP_PWM && HIGH_SIDE_PWM
		AnFET_off
	.elif HIGH_SIDE_PWM
		ApFET_off
	.else
		AnFET_off
	.endif
		in	temp2, PWM_A_PORT_in
.endmacro
.macro PWM_A_copy
		cpse	temp1, temp2
	.if !defined(AnFET) && COMP_PWM && HIGH_SIDE_PWM
		AnFET_on
	.elif HIGH_SIDE_PWM
		ApFET_on
	.else
		AnFET_on
	.endif
.endmacro

.macro PWM_B_on
	.if !defined(BnFET) && COMP_PWM && HIGH_SIDE_PWM
		BnFET_off
	.elif HIGH_SIDE_PWM
		BpFET_on
	.else
		BnFET_on
	.endif
.endmacro
.macro PWM_B_off
	.if !defined(BnFET) && COMP_PWM && HIGH_SIDE_PWM
		BnFET_on
	.elif HIGH_SIDE_PWM
		BpFET_off
	.else
		BnFET_off
	.endif
.endmacro
.macro PWM_B_clear
		in	temp1, PWM_B_PORT_in
	.if !defined(BnFET) && COMP_PWM && HIGH_SIDE_PWM
		BnFET_off
	.elif HIGH_SIDE_PWM
		BpFET_off
	.else
		BnFET_off
	.endif
		in	temp2, PWM_B_PORT_in
.endmacro
.macro PWM_B_copy
		cpse	temp1, temp2
	.if !defined(BnFET) && COMP_PWM && HIGH_SIDE_PWM
		BnFET_on
	.elif HIGH_SIDE_PWM
		BpFET_on
	.else
		BnFET_on
	.endif
.endmacro

.macro PWM_C_on
	.if !defined(CnFET) && COMP_PWM && HIGH_SIDE_PWM
		CnFET_off
	.elif HIGH_SIDE_PWM
		CpFET_on
	.else
		CnFET_on
	.endif
.endmacro
.macro PWM_C_off
	.if !defined(CnFET) && COMP_PWM && HIGH_SIDE_PWM
		CnFET_on
	.elif HIGH_SIDE_PWM
		CpFET_off
	.else
		CnFET_off
	.endif
.endmacro
.macro PWM_C_clear
		in	temp1, PWM_C_PORT_in
	.if !defined(CnFET) && COMP_PWM && HIGH_SIDE_PWM
		CnFET_off
	.elif HIGH_SIDE_PWM
		CpFET_off
	.else
		CnFET_off
	.endif
		in	temp2, PWM_C_PORT_in
.endmacro
.macro PWM_C_copy
		cpse	temp1, temp2
	.if !defined(CnFET) && COMP_PWM && HIGH_SIDE_PWM
		CnFET_on
	.elif HIGH_SIDE_PWM
		CpFET_on
	.else
		CnFET_on
	.endif
.endmacro
