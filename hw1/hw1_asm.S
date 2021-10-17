# @author Rafael Li (rafaell1@umbc.edu)
# @calendar.s
# ARMv8 assembly program that returns how many days are 
# in a specified calendar month/year.
#
#
#
# SOURCES
# https://developer.arm.com/documentation/ihi0055/latest
# First two registers are arguments from function
# https://azeria-labs.com/memory-instructions-load-and-store-part-4/
# Concept of memory in ARM, loading/storing
# https://azeria-labs.com/arm-conditional-execution-and-branching-part-6/
# branching instructions


#if defined(__clang__)
	.text
	.p2align 4
	.global _month_calc
_month_calc:
#else
	.section .text
	.globl month_calc
month_calc:
#endif
	# Load the month and leap year bool from C func

	str		x0, [sp, #0]
	ldr		x0, [sp, #0]
	str		x1, [sp, #16]
	ldr		x1, [sp, #16]
	
	# Check and go to which month is selected
	cmp		x0, #1
	b.eq	jan

	cmp		x0, #2
	b.eq	feb

	cmp		x0, #3
	b.eq	mar

	cmp		x0, #4
	b.eq	apr	

	cmp		x0, #5
	b.eq	may
	
	cmp		x0, #6
	b.eq	jun

	cmp		x0, #7
	b.eq	jul

	cmp		x0, #8
	b.eq	aug

	cmp		x0, #9
	b.eq	sep

	cmp		x0, #10
	b.eq	oct

	cmp		x0, #11
	b.eq	nov
	
	cmp		x0, #12
	b.eq	dec

	b		err

	# 32 bit block of memory for return value
	# number of days in month

jan:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

feb:
	cmp		x1, #0
	b.ne	leap
	mov		x0, #28
	str		x0, [sp, #48]
	b		end

leap:
	mov		x0, #29
	str		x0, [sp, #48]
	b		end

mar:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

apr:
	mov		x0, #30
	str		x0, [sp, #48]
	b		end

may:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

jun:
	mov		x0, #30
	str		x0, [sp, #48]
	b		end

jul:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

aug:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

sep:
	mov		x0, #30
	str		x0, [sp, #48]
	b		end

oct:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

nov:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

dec:
	mov		x0, #31
	str		x0, [sp, #48]
	b		end

err:
	mov		x0, #-1
	str		x0, [sp, #48]
	b		end

end:

	ret
