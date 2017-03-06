;-- Timing and motor debugging macros ------------------------------------

.macro flag_on
	.if MOTOR_DEBUG && (DIR_PB & (1<<4)) == 0
		sbi	PORTB, 4
	.endif
.endmacro
.macro flag_off
	.if MOTOR_DEBUG && (DIR_PB & (1<<4)) == 0
		cbi	PORTB, 4
	.endif
.endmacro
.macro sync_on
	.if MOTOR_DEBUG && (DIR_PB & (1<<3)) == 0
		sbi	PORTB, 3
	.elif MOTOR_DEBUG && (DIR_PB & (1<<5)) == 0
		sbi	PORTB, 5
	.endif
.endmacro
.macro sync_off
	.if MOTOR_DEBUG && (DIR_PB & (1<<3)) == 0
		cbi	PORTB, 3
	.elif MOTOR_DEBUG && (DIR_PB & (1<<5)) == 0
		cbi	PORTB, 5
	.endif
.endmacro
