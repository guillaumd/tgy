
;-- Complementary PWM macros ---------------------------------------------

.if CPWM_SOFT
	.macro PWM_COMP_A_on
		.if HIGH_SIDE_PWM
			AnFET_on
		.else
			ApFET_on
		.endif
	.endmacro

	.macro PWM_COMP_A_off
		.if HIGH_SIDE_PWM
			AnFET_off
		.else
			ApFET_off
		.endif
	.endmacro

	.macro PWM_COMP_B_on
		.if HIGH_SIDE_PWM
			BnFET_on
		.else
			BpFET_on
		.endif
	.endmacro

	.macro PWM_COMP_B_off
		.if HIGH_SIDE_PWM
			BnFET_off
		.else
			BpFET_off
		.endif
	.endmacro

	.macro PWM_COMP_C_on
		.if HIGH_SIDE_PWM
			CnFET_on
		.else
			CpFET_on
		.endif
	.endmacro

	.macro PWM_COMP_C_off
		.if HIGH_SIDE_PWM
			CnFET_off
		.else
			CpFET_off
		.endif
	.endmacro
.endif
