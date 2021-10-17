/* YOUR FILE-HEADER COMMENT HERE */

#if defined(__clang__)
	.text
	.p2align 4
# define FUNC_NAME(x) _##x
# define DEFINE_FUNC(x) .global FUNC_NAME(x) __NL__ FUNC_NAME(x):
#else
	.section .text
# define FUNC_NAME(x) x
# define DEFINE_FUNC(x) .globl FUNC_NAME(x) __NL__ FUNC_NAME(x):
	#endif

DEFINE_FUNC(uint16_mult_asm)
	// x0 = multiplicand
	// x1 = multiplier

	/* PART 2: YOUR CODE HERE */
	/* This implements booth's algorithm */
	// x1 is reused to store lower half of product
	mov x2, x0 // new multiplicand
	mov x0, #0 // top half of product
	mov x3, #16 // counter
	mov x4, #0 // extra digit to right of product's LSB

booths_top:
	// collect lower two bits into temp register X5
	mov x5, x4
	bfi x5, x1, #1, #1
	// check if should add, subtract, or do nothing
	cmp x5, #0x1
	b.eq booths_add_multiplicand
	cmp x5, #0x2
	b.ne booths_shift

	// subtract from upper half
	sub x0, x0, x2
	b booths_shift
booths_add_multiplicand:
	// add to upper half
	add x0, x0, x2

booths_shift:
	// move LSB of lower into temp x4
	and x4, x1, #1
	// shift LSB of x0 to MSB of x1
	and x5, x0, #1
	asr x0, x0, #1
	asr x1, x1, #1
	bfi x1, x5, #15, #1

	subs x3, x3, #1
	b.ne booths_top
	mov x0, x1  // return only lower 16 bits of product
	ret

DEFINE_FUNC(uint16_div_asm)
	// x0 = dividend
	// x1 = divisor
	/* PART 3: YOUR CODE HERE */
	mov x2, x1  // new divisor
	mov x1, x0  // lower half of R/Q
	mov x0, #0  // new upper half of R/Q
	mov x3, #16 // counter
shift_sub3_top:
	ubfx x4, x1, #15, #1
	lsl x0, x0, #1
	orr x0, x0, x4
	lsl x1, x1, #1
	cmp x0, x2
	b.lt shift_sub3_bottom
	sub x0, x0, x2
	orr x1, x1, #1
shift_sub3_bottom:
	subs x3, x3, #1
	b.ne shift_sub3_top
	mov x0, x1  // return only the quotient
	ret
	
DEFINE_FUNC(uint16_mult_asm_shift_adder_3)
	/* This implements shift-add, version 3 */
	// x1 is reused to store lower half of product
	mov x2, x0 // new multiplicand
	mov x0, #0 // top half of product
	mov x3, #16 // counter

	mov x4, #0 // top half of multiplier (and top half of product)
	mov x5, #16 // counter

shift_adder3_top:
	and x4, x1, #1
	cmp x4, #1
	b.ne shift_adder3_shift
	add x0, x0, x2
shift_adder3_shift:
	and x4, x0, #1
	lsr x0, x0, #1
	lsr x1, x1, #1
	bfi x1, x4, #15, #1
	subs x3, x3, #1
	b.ne shift_adder3_top
	mov x0, x1  // return only lower 16 bits of product
	ret
