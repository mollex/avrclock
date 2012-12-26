;---------------------------------------------------------------------------;
; MMC hardware dmd     (C)mlx, 2012
;---------------------------------------------------------------------------;
; Hardware dependent macros to be modified
/*
	Return values are expected to be passed in a similar fashion. An 8-bit value is passed via R24,
	a 16-bit value in R25:R24, up to 32-bits in R22:R23:R24:R25. 8-bit return values are zero/sign-extended
	to 16-bits by the called function.
*/

#define	DDR_CK1	_SFR_IO_ADDR(DDRB), 5
#define	PORT_CK1	_SFR_IO_ADDR(PORTB), 5

#define	DDR_MOSI1	_SFR_IO_ADDR(DDRB), 3
#define	PORT_MOSI1	_SFR_IO_ADDR(PORTB), 3

#define	DDR_MOSI2	_SFR_IO_ADDR(DDRB), 4
#define	PORT_MOSI2	_SFR_IO_ADDR(PORTB), 4

;---------------------------------------------------------------------------;
.nolist
#include <avr/io.h>
.list
.text


;---------------------------------------------------------------------------;
; Initialize dmd soft spi1
;
; void xinit_spi1 (void);

.global xinit_spi1
.func xinit_spi1
xinit_spi1:
	sbi	DDR_MOSI1	; MOSI1 output
	cbi	PORT_MOSI1
	sbi	DDR_CK1		; SCLK: output
	ret
.endfunc

;---------------------------------------------------------------------------;
; Initialize dmd soft spi2
;
; void xinit_spi2 (void);

.global xinit_spi2
.func xinit_spi2
xinit_spi2:
	sbi	DDR_MOSI2	; MOSI2 output
	sbi	PORT_MOSI2
	sbi	DDR_CK1		; SCLK: output
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
	cbi	PORT_MOSI1		;
	sbrs	r24, 0		;
	sbi	PORT_MOSI1		; /
	sbi	PORT_CK1		; A positive pulse to SCLK
	lsr	r24				; Get DO from MMC
	cbi	PORT_CK1		; /
	dec	r26				; Repeat 8 times
	brne	1b			; /
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
	cbi	PORT_MOSI1		;
	sbrs	r25, 0		;
	sbi	PORT_MOSI1		; /
	sbi	PORT_CK1		; A positive pulse to SCLK
	lsr	r25				; Get DO from MMC
	cbi	PORT_CK1		; /
	dec	r26				; Repeat 8 times
	brne	2b			; /
	ret
.endfunc

;---------------------------------------------------------------------------;
; Transmit a short
;
; void xshort_spi1 (short);

.global xshort_spi1
.func xshort_spi1
xshort_spi1:
	ldi	r26, 8

11:	sbrc	r24, 0		; DI = Bit to sent
	cbi	PORT_MOSI1		;
	sbrs	r24, 0		;
	sbi	PORT_MOSI1		; /
	sbi	PORT_CK1		; A positive pulse to SCLK
	lsr	r24				; Get DO from MMC
	cbi	PORT_CK1		; /
	dec	r26				; Repeat 8 times
	brne	11b			; /

	ldi	r26, 8
12:	sbrc	r25, 0		; DI = Bit to sent
	cbi	PORT_MOSI1		;
	sbrs	r25, 0		;
	sbi	PORT_MOSI1		; /
	sbi	PORT_CK1		; A positive pulse to SCLK
	lsr	r25				; Get DO from MMC
	cbi	PORT_CK1		; /
	dec	r26				; Repeat 8 times
	brne	12b			; /

	ret
.endfunc
