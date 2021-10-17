# @author Rafael Li, rafaell1@umbc.edu
# @hw2_asm.S
# ARMv8 assembly program that returns how many days are 
# in a specified calendar month/year.


#if defined(__clang__)
	.text
	.p2align 4
# define FUNC_NAME(x) _##x
# define DEFINE_FUNC(x) .global AFUNC_NAME(x) __NL__ FUNC_NAME(x):
#else
	.section .text
# define FUNC_NAME(x) x
# define DEFINE_FUNC(x) .globl FUNC_NAME(x) __NL__ FUNC_NAME(x):
	#endif

DEFINE_FUNC(asm_is_divisible_by_7_tail_recursive)
	/* PART 3: YOUR CODE HERE */
	b		loop

divisible:
	mov		x0, #1
	b		end

nondiv:
	mov		x0, #0
	b		end

end:
	ret

loop:
	# Nondiv if less than 0
	cmp		x0, #0
	b.lt	nondiv

	
	sub		x0, x0, #7

	# Divisible if 0, no remainder
	cmp		x0, #0
	b.eq	divisible
	cmp		x0, #0
	b.lt	nondiv

	b		check

check:
	# Loops if val is greater than 0
	cmp		x0, #0
	b.gt	loop

DEFINE_FUNC(asm_memcpy_256bit)
	/* PART 5: YOUR CODE HERE */
	sub		sp, sp, #128
	str		x0, [sp, #64]
	str		x1, [sp, #32]
	str		x2, [sp, #16]

copy:
	ldp		x6, x7, [x0]
	ldp		x8, x9, [x0, #16]
	stp		x6, x7, [x1]
	stp		x8, x9, [x1, #16]

	ldr		x0, [sp, #64]
	add		x0, x0, #32
	str		x0, [sp, #64]

	ldr		x1, [sp, #32]
	add		x1, x1, #32
	str		x1, [sp, #32]

	ldr		x2, [sp, #16]
	sub		x2, x2, #32
	str		x2, [sp, #16]

	ldr		x2, [sp, #16]
	cmp		x2, #0
	b.gt	copy

	add		sp, sp, #128

	ret
