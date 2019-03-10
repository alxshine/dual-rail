	.text
	.syntax unified
	.eabi_attribute	67, "2.09"
	.cpu	cortex-m0
	.eabi_attribute	6, 12
	.eabi_attribute	7, 77
	.eabi_attribute	8, 0
	.eabi_attribute	9, 1
	.eabi_attribute	34, 0
	.eabi_attribute	17, 1
	.eabi_attribute	20, 1
	.eabi_attribute	21, 1
	.eabi_attribute	23, 3
	.eabi_attribute	24, 1
	.eabi_attribute	25, 1
	.eabi_attribute	38, 1
	.eabi_attribute	18, 4
	.eabi_attribute	26, 2
	.eabi_attribute	14, 0
	.file	"program.c"
	.globl	c_entry
	.p2align	1
	.type	c_entry,%function
	.code	16
	.thumb_func
c_entry:
	.fnstart
	.pad	#4
	sub	sp, #4
	movs	r0, #0
	str	r0, [sp]
	b	.LBB0_1
.LBB0_1:
	ldr	r0, [sp]
	cmp	r0, #9
	bgt	.LBB0_3
	b	.LBB0_2
.LBB0_2:
	ldr	r0, [sp]
	adds	r0, r0, #1
	str	r0, [sp]
	b	.LBB0_1
.LBB0_3:
	add	sp, #4
	bx	lr
.Lfunc_end0:
	.size	c_entry, .Lfunc_end0-c_entry
	.cantunwind
	.fnend


	.ident	"clang version 7.0.1 (tags/RELEASE_701/final)"
	.section	".note.GNU-stack","",%progbits
	.addrsig
	.addrsig_sym c_entry
	.eabi_attribute	30, 6
