;---------------------------------------------------------------------------;
; MMC hardware dmd     (C)mlx, 2012
;---------------------------------------------------------------------------;
; Hardware dependent macros to be modified
/*
	Return values are expected to be passed in a similar fashion. An 8-bit value is passed via R24,
	a 16-bit value in R25:R24, up to 32-bits in R22:R23:R24:R25. 8-bit return values are zero/sign-extended
	to 16-bits by the called function.
*/
//#define	DDR_CS	_SFR_IO_ADDR(DDRC), 0	// MMC CS pin (DDR, PORT)
//#define	PORT_CS	_SFR_IO_ADDR(PORTC), 0

#define	DDR_CK	_SFR_IO_ADDR(DDRB), 5
#define	PORT_CK	_SFR_IO_ADDR(PORTB), 5

#define	DDR_DI	_SFR_IO_ADDR(DDRB), 3
#define	PORT_DI	_SFR_IO_ADDR(PORTB), 3

#define	PIN_DO	_SFR_IO_ADDR(PINB), 4
#define	PORT_DO	_SFR_IO_ADDR(PORTB), 4


;---------------------------------------------------------------------------;
.nolist
#include <avr/io.h>
.list
.text


;---------------------------------------------------------------------------;
; Initialize MMC port
;
; void xinit_spi1 (void);

.global xinit_spi1
.func xinit_spi1
xinit_spi1:
	//sbi	DDR_CS		; CS: output
	sbi	DDR_DI		; DI: output
	sbi	DDR_CK		; SCLK: output
	sbi	PORT_DO		; DO: pull-up
	ret
.endfunc


;---------------------------------------------------------------------------;
; Transmit a byte
;
; void xlow_spi1 (char);

.global xlow_spi1
.func xlow_spi1
xlow_spi1:
	ldi	r26, 8
1:	sbrc	r24, 0		; DI = Bit to sent
	cbi	PORT_DI		;
	sbrs	r24, 0		;
	sbi	PORT_DI		; /
	sbi	PORT_CK		; A positive pulse to SCLK
	lsr	r24		; Get DO from MMC
	cbi	PORT_CK		; /
	dec	r26		; Repeat 8 times
	brne	1b		; /
	ret
.endfunc

;---------------------------------------------------------------------------;
; Transmit a byte
;
; void xdmd_spi1 (short);

.global xhigh_spi1
.func xhigh_spi1
xhigh_spi1:
	ldi	r26, 8
2:	sbrc	r25, 0		; DI = Bit to sent
	cbi	PORT_DI		;
	sbrs	r25, 0		;
	sbi	PORT_DI		; /
	sbi	PORT_CK		; A positive pulse to SCLK
	lsr	r25		; Get DO from MMC
	cbi	PORT_CK		; /
	dec	r26		; Repeat 8 times
	brne	2b		; /
	ret
.endfunc


