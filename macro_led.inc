;-- LED macros -----------------------------------------------------------

.if !defined(red_led)
	.macro RED_on
	.endmacro
	.macro RED_off
	.endmacro
.endif

.if !defined(green_led)
	.macro GRN_on
	.endmacro
	.macro GRN_off
	.endmacro
.endif

.if !defined(blue_led)
	.macro BLUE_on
	.endmacro
	.macro BLUE_off
	.endmacro
.endif
