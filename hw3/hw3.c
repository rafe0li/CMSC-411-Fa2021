/* YOUR FILE-HEADER COMMENT HERE */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Given a 16-bit binary value, break down its IEEE-754 half-precision
 * floating point representation.
 *
 * Display the sign bit, un-biased exponent, and significand
 * (including the leading implied bit). If the value is normal,
 * display what kind of value it is. For infinity and NaN, the leading
 * implied bit is a don't care, and the actual magnitude is a don't
 * care.
 *
 * @param[in] val 16-bit floating point value to analyze.
 */
static void half_float_parse(uint16_t val)
{
	_Float16 f = *((_Float16*)&(val));
	printf("For the bit pattern 0x%04x (half float value: %g):\n", val,
		(float)f);

	// Shifts bits until at LSB to isolate with bit mask
	// Isolates sign bit, exponent bits, and mantissa bits
	int sign = (val >> 15) & 0x1;
	int exp = (val >> 10) & 0x1f;
	int frac = val & 0x3ff;
	// Bit for whether value is normal or not, 1 if normal
	int normal = 1;
	// True if value is infinity or nan
	int infnan = 0;

	// Right shifts n - 1 places on values that are n bits long
	// Reverses order of bits
	exp = exp >> 4;
	frac = frac >> 9;

	// Conditions for type of floating point value
	if (exp == 0 && frac == 0) {
		// Negative Zero
		if (sign == 1) {
			printf("\nVALUE TYPE: Negative Zero\n");
			normal = 0;
		}
		// Denormalized
		else {
			printf("\nVALUE TYPE: Denormalized\n");
			normal = 0;
		}
	}
	else if (exp == 31) {
		// Infinity
		if (frac == 0) {
			printf("\nVALUE TYPE: Infinity\n");
			normal = 0;
		}
		// NaN
		else {
			printf("\nVALUE TYPE: Not a Number/NaN\n");
			normal = 0;
		}
		infnan = 1;
	}

	val = val << 4;

	printf("\nVAL SIGNIFICAND: [%d]\n", frac);

	if (normal) {
		printf("\nVALUE TYPE: Normal\n");
	}
	printf("\nSign Bit: [%d]\n", sign);
	printf("\nExponent in decimal: [%d]\n", exp);
	// Subtract offset if value is normal
	if (normal == 1) {
		exp = exp - 15;
		printf("Actual Magnitude of Exponent: [%d]\n", exp);
	}
	if (infnan) {
		printf("\nSignificand Bits in Hex: [0xX%X]\n\n", frac);
	}
	else {
		printf("\nSignificand Bits in Hex: [0x%X]\n\n", frac);
	}
}

/**
 * Perform 16-bit unsigned integer multiplication of @a i1 and @a i2,
 * returning the lower 16-bits of the product.
 *
 * You have your choice of whatever shift-add algorithm to
 * implement. You MAY NOT simply loop like this:
 * <pre>
 *    uint16_t product = 0;
 *    while (i2-- > 0)
 *        product += i1;
 *    return i1;
 * </pre>
 * This code must use bit manipulation to find the product.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, bitmasks, compare, and branch operations. You
 * <strong>may not</strong> use any built-in multiplication or
 * division instructions for this part.
 *
 * @param[in] i1 Multiplicand
 * @param[in] i2 Multiplier
 * @return Lower 16 bits of product
 */
static uint16_t uint16_mult(uint16_t i1, uint16_t i2)
{
	uint16_t prod = 0;
	int i;
	// If LSB of multiplier is 1, then add multiplicand to product
	if ((i2 & 0x1) == 1) {
		prod += i2;
	}
	// Shifts multiplicand left and multiplier right
	i1 = i1 << 1;
	i2 = i2 >> 1;
	for (i = 0; i < 16; i++) {
		if ((i2 & 0x1) == 1) {
			prod += i2;
		}
		i1 = i1 << 1;
		i2 = i2 >> 1;
	}
	return prod;
}

/**
 * Perform 16-bit unsigned integer division of @a i1 by @a i2,
 * returning the quotient.
 *
 * You have your choice of whatever shift-subtract algorithm to
 * implement. You MAY NOT simply loop like this:
 * <pre>
 *    uint16_t quotient = 0;
 *    while (ii > i2) {
 *        i1 -= i2;
 *        quotient++;
 *    }
 *    return quotient;
 * </pre>
 * This code must use bit manipulation to find the quotient.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, bitmasks, compare, and branch operations. You
 * <strong>may not</strong> use any built-in multiplication or
 * division instructions for this part.
 *
 * @param[in] i1 Dividend
 * @param[in] i2 Divisor, guaranteed to be non-zero
 * @return quotient
 */
static uint16_t uint16_div(uint16_t i1, uint16_t i2)
{
	return 0;
}

/**
 * Perform 16-bit unsigned integer multiplication of @a i1 and @a i2,
 * returning the lower 16-bits of the product.
 *
 * You have your choice of whatever shift-subtract algorithm to
 * implement. Like uint16_mult(), you MAY NOT simply loop.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, bitmasks, compare, and branch operations. You
 * <strong>may not</strong> use any built-in multiplication or
 * division instructions for this part.
 *
 * @param[in] i1 Multiplicand
 * @param[in] i2 Multiplier
 * @return Lower 16 bits of product
 */
extern uint16_t uint16_mult_asm(uint16_t i1, uint16_t i2);

/**
 * Perform 16-bit unsigned integer division of @a i1 by @a i2,
 * returning the quotient.
 *
 * You have your choice of whatever shift-subtract algorithm to
 * implement. Like uint16_div(), you MAY NOT simply loop.
 *
 * SPECIAL RESTRICTION: you may only use addition, subtraction,
 * shifts, rotate, bitmasks, compare, and branch operations. You
 * <strong>may not</strong> use any built-in multiplication or
 * division instructions for this part.
 *
 * @param[in] i1 Dividend
 * @param[in] i2 Divisor, guaranteed to be non-zero
 * @return quotient
 */
extern uint16_t uint16_div_asm(uint16_t i1, uint16_t i2);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Need at least two arguments\n");
		exit(EXIT_FAILURE);
	}

	char* endptr;
	unsigned long long arg1 = strtoull(argv[1], &endptr, 0);
	if (!(*(argv[1])) || *endptr) {
		fprintf(stderr, "Argument 1 not a number: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	unsigned long long arg2 = strtoull(argv[2], &endptr, 0);
	if (!*(argv[2]) || *endptr) {
		fprintf(stderr, "Argument 2 not a number: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	uint16_t i1 = (uint16_t)arg1;
	uint16_t i2 = (uint16_t)arg2;

	half_float_parse(i1);
	half_float_parse(i2);

	printf("Part 2: multiplying %u and %u:\n", i1, i2);
	uint16_t correct_product = i1 * i2;
	printf("  Correct product: %u\n", correct_product);
	uint16_t part2_product_c = uint16_mult(i1, i2);
	printf("   uint16_mult product: %u\n", part2_product_c);
	uint16_t part2_product_asm = uint16_mult_asm(i1, i2);
	printf("   uint16_mult_asm product: %u\n", part2_product_asm);

	if (i2 == 0) {
		fprintf(stderr, "Argument 2 may not be zero\n");
		exit(EXIT_FAILURE);
	}

	printf("Part 3: dividing %u by %u:\n", i1, i2);
	uint16_t correct_quotient = i1 / i2;
	printf("  Correct quotient: %u\n", correct_quotient);
	uint16_t part3_quotient_c = uint16_div(i1, i2);
	printf("   uint16_div quotient: %u\n", part3_quotient_c);
	uint16_t part3_quotient_asm = uint16_div_asm(i1, i2);
	printf("   uint16_div_asm product: %u\n", part3_quotient_asm);

	return 0;
}