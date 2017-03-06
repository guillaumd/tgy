;-- Analog comparator sense macros ---------------------------------------
; We enable and disable the ADC to override ACME when one of the sense
; pins is AIN1 instead of an ADC pin. In the future, this will allow
; reading from the ADC at the same time.

.macro comp_init
		in	@0, SFIOR
		sbr	@0, (1<<ACME)	; set Analog Comparator Multiplexer Enable
		out	SFIOR, @0
	.if defined(mux_a) && defined(mux_b) && defined(mux_c)
		cbi	ADCSRA, ADEN	; Disable ADC to make sure ACME works
	.endif
.endmacro
.macro comp_adc_disable
	.if !defined(mux_a) || !defined(mux_b) || !defined(mux_c)
		cbi	ADCSRA, ADEN	; Disable ADC if we enabled it to get AIN1
	.endif
.endmacro
.macro comp_adc_enable
		sbi	ADCSRA, ADEN	; Eisable ADC to effectively disable ACME
.endmacro
.macro set_comp_phase_a
	.if defined(mux_a)
		ldi	@0, mux_a	; set comparator multiplexer to phase A
		out	ADMUX, @0
		comp_adc_disable
	.else
		comp_adc_enable
	.endif
.endmacro
.macro set_comp_phase_b
	.if defined(mux_b)
		ldi	@0, mux_b	; set comparator multiplexer to phase B
		out	ADMUX, @0
		comp_adc_disable
	.else
		comp_adc_enable
	.endif
.endmacro
.macro set_comp_phase_c
	.if defined(mux_c)
		ldi	@0, mux_c	; set comparator multiplexer to phase C
		out	ADMUX, @0
		comp_adc_disable
	.else
		comp_adc_enable
	.endif
.endmacro

