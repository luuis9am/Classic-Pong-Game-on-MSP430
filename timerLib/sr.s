	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

	.global set_sr
set_sr: nop
	mov r12, r2
	nop
	ret

	.global get_sr
get_sr:	nop
	mov r2, r12
	nop
	ret

	.global or_sr
or_sr:	nop
	bis r12, r2
	nop
	ret
	
	.global and_sr
and_sr:	nop
	and r12, r2
	nop
	ret
