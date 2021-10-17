/*
* @author Rafael Li, rafaell1@umbc.edu
* @hw2.c
* C program that prints out the execution times of
* several functions, including an empty, fibonacci, and
* divisibility function. Calls ARMv8 assembly for a 
* recursive subroutine and for a 32-byte memcpy routine.
*/

/* There were 5 instructions in the unoptimized version of the
 * disassembly of do_nothing as opposed to 2 instructions in the 
 * optimized version. The unoptimized version allocates space on
 * the stack pointer, stores and loads from w0, and restores the space
 * on the stack. The optimized version, on the other hand, does not
 * allocate memory at all, it simply has a nop and returns.
 */

#define _POSIX_C_SOURCE 199309L

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(__clang__)
#define OPTIMIZED minsize
#define UNOPTIMIZED optnone
#else
#define OPTIMIZED optimize("O2")
#define UNOPTIMIZED optimize("O0")
#endif

/**
 * Number of times to execute target function.
 */
#define NUM_TRIALS 50

/**
 * This function does nothing, intentionally.
 */
static int __attribute__((OPTIMIZED)) do_nothing(int val)
{
	return val;
}

/**
 * Calculate the nth value in the Fibonacci sequence, unoptimized.
 * <strong>You do not need to modify this function.</strong>
 * @param[in] n Which Fibonacci number to return.
 * @return Value of the @a n-th Fibonacci number.
 */
static int __attribute__((UNOPTIMIZED)) fibonacci_unoptimized(int n)
{
	if (n <= 1)
		return n;
	return fibonacci_unoptimized(n - 1) + fibonacci_unoptimized(n - 2);
}

/**
 * Calculate the nth value in the Fibonacci sequence, optimized.
 * <strong>You do not need to modify this function.</strong>
 * @param[in] n Which Fibonacci number to return.
 * @return Value of the @a n-th Fibonacci number.
 */
static int __attribute__((OPTIMIZED)) fibonacci_optimized(int n)
{
	if (n <= 1)
		return n;
	return fibonacci_optimized(n - 1) + fibonacci_optimized(n - 2);
}

/**
 * Calculate if the given parameter is evenly divisible by 7.
 *
 * <strong>SPECIAL RESTRICTION</strong>: This function may only be
 * written using an <strong>ITERATIVE</strong> loop. It may not use
 * multiplication, division, or modulus operator.
 *
 * @param[in] n Value to determine
 * @return 1 if @a n is divisible by 7, 0 if not divisible by 7, -1 if
 * @a n is negative.
 */
static int __attribute((UNOPTIMIZED)) is_divisible_by_7_iterative(int n)
{
	/* PART 3: YOUR CODE HERE */

	while (n > 0)
		n = n - 7;
	if (n < 0)
		return 0;
	return 1;
}

/**
 * Calculate if the given parameter is evenly divisible by 7.
 *
 * <strong>SPECIAL RESTRICTION</strong>: This function may only be
 * written using a <strong>RECURSIVE</strong> call. It may not use
 * multiplication, division, or modulus operator.
 *
 * @param[in] n Value to determine
 * @return 1 if @a n is divisible by 7, 0 if not divisible by 7, -1 if
 * @a n is negative.
 */
static int __attribute((UNOPTIMIZED)) is_divisible_by_7_recursive(int n)
{
	/* PART 3: YOUR CODE HERE */
	if (n < 0)
		return 0;
	is_divisible_by_7_recursive(n - 7);
	return 1;
}

/**
 * Calculate if the given parameter is evenly divisible by 7.
 *
 * <strong>SPECIAL RESTRICTION</strong>: This function may only be
 * written using a <strong>TAIL RECURSIVE</strong> call. It may not use
 * multiplication, division, or modulus instructions.
 *
 * @param[in] n Value to determine
 * @return 1 if @a n is divisible by 7, 0 if not divisible by 7, -1 if
 * @a n is negative.
 */
extern int asm_is_divisible_by_7_tail_recursive(int n);

/**
 * Copy bytes from @a src to @a dst.
 * <strong>You do not need to modify this function.</strong>
 * @param[out] dst Starting address for destination buffer
 * @param[in] src Starting address for source buffer
 * @param[in] n Number of bytes to copy
 * @return Always @a dst
 */
void *memcpy_8bit(void *restrict dst, const void *restrict src, size_t n)
{
	uint8_t *restrict d = (uint8_t * restrict)dst;
	const uint8_t *restrict s = (const uint8_t * restrict)src;
	while (n > 0) {
		*d = *s;
		d++;
		s++;
		n--;
	}
	return dst;
}

/**
 * Copy bytes from @a src to @a dst, in increments of 64 bits (8
 * bytes) at a time.
 * <strong>You do not need to modify this function.</strong>
 * @param[out] dst Starting address for destination buffer
 * @param[in] src Starting address for source buffer
 * @param[in] n Number of bytes to copy. This must be evenly divisible
 * by 8.
 * @return Always @a dst
 */
void *memcpy_64bit(void *restrict dst, const void *restrict src, size_t n)
{
	uint64_t *restrict d = (uint64_t * restrict)dst;
	const uint64_t *restrict s = (const uint64_t * restrict)src;
	while (n > 0) {
		*d = *s;
		d++;
		s++;
		n -= 8;
	}
	return dst;
}

/**
 * Copy bytes from @a src to @a dst, in increments of 256 bits (32
 * bytes) at a time.
 * @param[out] dst Starting address for destination buffer
 * @param[in] src Starting address for source buffer
 * @param[in] n Number of bytes to copy. This must be evenly divisible
 * by 32.
 * @return Always @a dst
 */
extern void *asm_memcpy_256bit(void *restrict dst, const void *restrict src,
			       size_t n);

/**
 * Calculate and return the difference between two clock values.
 * <strong>You do not need to modify this function.</strong>
 * @param[in] stop Minuend to subtract from
 * @param[in] start Subtrahend to subtract
 * @return Number of nanoseconds that elapsed
 */
static unsigned long clock_diff(const struct timespec *stop,
				const struct timespec *start)
{
	time_t sec_diff = stop->tv_sec - start->tv_sec;
	unsigned long nsec_diff;
	if (stop->tv_nsec < start->tv_nsec) {
		nsec_diff = 1000000000lu + stop->tv_nsec - start->tv_nsec;
		sec_diff--;
	} else
		nsec_diff = stop->tv_nsec - start->tv_nsec;
	nsec_diff += 1000000000lu * sec_diff;
	return nsec_diff;
}

typedef int (*func1)(int);
typedef void *(*func3)(void *restrict, const void *restrict, size_t);

/**
 * Lambda to qsort(), to sort a list of unsigned longs in ascending
 * order.
 */
static int ul_comp(const void *p1, const void *p2)
{
	unsigned long a = *((unsigned long *)(p1));
	unsigned long b = *((unsigned long *)(p2));
	return b - a;
}

static double overhead_time;

/**
 * Calculate the execution time for a function, given a series of data
 * points. Compensate for how long it takes to measure time itself.
 *
 * <strong>You do not need to modify this function.</strong>
 *
 * @param[in] samples Array of raw execution times
 * @param[in] num_elems Number of elements in @a samples
 * @return Average execution time, in nanoseconds
 */
static double calc_execution_time(unsigned long *samples, unsigned num_elems)
{
	qsort(samples, NUM_TRIALS, sizeof(samples[0]), ul_comp);
	double median;
	median = samples[NUM_TRIALS / 2];
	if (median >= overhead_time)
		return median - overhead_time;
	return 0.1;
}

/**
 * Measure how long the system timing takes itself to execute.
 * <strong>You do not need to modify this function.</strong>
 * @return Overhead time, in nanoseconds
 */
static void measure_overhead(void)
{
	unsigned long samples[NUM_TRIALS];
	overhead_time = 0;
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		clock_gettime(CLOCK_MONOTONIC, &stop);
		samples[i] = clock_diff(&stop, &start);
	}
	overhead_time = calc_execution_time(samples, NUM_TRIALS);
}

/**
 * Measure how long it takes to execute a function, passing it one
 * parameter. Call it multiple times, and return the median execution
 * time.
 *
 * <strong>You do not need to modify this function.</strong>
 *
 * @param[in] target_func Function to execute
 * @param[in] val Parameter to pass into function
 * @param[out] retval Return value from calling @a target_func
 * @return Median execution time, in nanoseconds
 */
static double measure_function1(func1 target_func, int val, int *retval)
{
	unsigned long samples[NUM_TRIALS];
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		int r;
		clock_gettime(CLOCK_MONOTONIC, &start);
		r = target_func(val);
		clock_gettime(CLOCK_MONOTONIC, &stop);
		*retval = r;
		samples[i] = clock_diff(&stop, &start);
	}
	return calc_execution_time(samples, NUM_TRIALS);
}

/**
 * Measure how long it takes to execute
 * asm_is_divisible_by_7_tail_recursive() three times, against an
 * array of 3 parameters. Return the median execution time.
 *
 * <strong>You do not need to modify this function.</strong>
 *
 * @param[in] part4_args Array of values to pass into
 * asm_is_divisible_by_7_tail_recursive()
 * @return Median execution time, in nanoseconds
 */
static double measure_div7_calls(int *part4_args)
{
	unsigned long samples[NUM_TRIALS];
	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		asm_is_divisible_by_7_tail_recursive(part4_args[0]);
		asm_is_divisible_by_7_tail_recursive(part4_args[1]);
		asm_is_divisible_by_7_tail_recursive(part4_args[2]);
		clock_gettime(CLOCK_MONOTONIC, &stop);
		samples[i] = clock_diff(&stop, &start);
	}
	return calc_execution_time(samples, NUM_TRIALS);
}

/**
 * Measure how long it takes to execute a memcpy()-like function,
 * passing three parameters. Call it multiple times, and return the
 * median execution time.
 *
 * <strong>You do not need to modify this function.</strong>
 *
 * @param[in] target_func Function to execute
 * @param[in] n Number of bytes to copy
 * @param[out] retval Return value from calling @a target_func
 * @return Median execution time, in nanoseconds
 */
static double measure_function3(func3 target_func, size_t n)
{
	static unsigned seed = 0;
	unsigned long samples[NUM_TRIALS];
	unsigned char *src = malloc(n);
	if (!src) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	unsigned char *dst = malloc(n);
	if (!dst) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	seed++;
	memset(src, 0xa5 + seed, n);
	memset(dst, 0x5a - seed, n);

	target_func(dst, src, n);
	unsigned char *s = src;
	unsigned char *d = dst;
	for (size_t i = 0; i < n; i++) {
		if (*s != *d) {
			fprintf(stderr,
				"WARNING! memcpy implementation is incorrect!\n");
			fprintf(stderr, "First incorrect byte:\n");
			fprintf(stderr,
				"  offset %zu: is 0x%02x, should be 0x%02x\n",
				i, *d, *s);
			exit(EXIT_FAILURE);
		}
		s++;
		d++;
	}

	for (unsigned i = 0; i < NUM_TRIALS; i++) {
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		target_func(dst, src, n);
		clock_gettime(CLOCK_MONOTONIC, &stop);
		samples[i] = clock_diff(&stop, &start);
	}

	free(src);
	free(dst);
	return calc_execution_time(samples, NUM_TRIALS);
}

int main(int argc, char *argv[])
{
	measure_overhead();

	int retval;
	double time_do_nothing = measure_function1(do_nothing, 0, &retval);
	printf("PART 1:\n");
	printf("do_nothing: execution time = %f ns\n", time_do_nothing);

	if (argc < 2) {
		fprintf(stderr, "Need at least one argument to continue\n");
		exit(EXIT_FAILURE);
	}
	int target = atoi(argv[1]);

	printf("\nPART 2:\n");
	double time_fib_unopt =
	    measure_function1(fibonacci_unoptimized, target, &retval);
	printf
	    ("fibonacci (unoptimized): result = %d, execution time = %f ns\n",
	     retval, time_fib_unopt);
	double time_fib_opt =
	    measure_function1(fibonacci_optimized, target, &retval);
	printf("fibonacci (optimized): result = %d, execution time = %f ns\n\n",
	       retval, time_fib_opt);
	/* PART 2: YOUR CODE HERE */

	/* Next Fibonacci number should take [initial speed] ns * 1.618  
	* 
	 * 
	 * Predictions for Fibonacci numbers 15-20:
	 * Multiple runs for 15 consistently show about
	 * 24000 ns for unoptimized and 12000 for optimized
	 * 
	 */

	double fibTime = 1.618;
	double avgUnopt = 24000;
	double avgOpt = 12000;
	double unoptPredict1 = avgUnopt * fibTime;
	double unoptPredict2 = unoptPredict1 * fibTime;
	double unoptPredict3 = unoptPredict2 * fibTime;
	double unoptPredict4 = unoptPredict3 * fibTime;
	double unoptPredict5 = unoptPredict4 * fibTime;
	double optPredict1 = avgOpt * fibTime;
	double optPredict2 = optPredict1 * fibTime;
	double optPredict3 = optPredict2 * fibTime;
	double optPredict4 = optPredict3 * fibTime;
	double optPredict5 = optPredict4 * fibTime;


	double time_fib_unopt1 =
		measure_function1(fibonacci_unoptimized, target + 1, &retval);
	double time_fib_opt1 =
		measure_function1(fibonacci_optimized, target + 1, &retval);
	printf
	("measuring Fibonacci number #16: result = %d, \n\t unoptimized: predicted = %lf ns, actual = %lf ns \n\t optimized: predicted = %lf ns, actual = %lf ns\n",
		retval, unoptPredict1, time_fib_unopt1, optPredict1, time_fib_opt1);

	double time_fib_unopt2 =
		measure_function1(fibonacci_unoptimized, target + 2, &retval);
	double time_fib_opt2 =
		measure_function1(fibonacci_optimized, target + 2, &retval);
	printf
	("measuring Fibonacci number #17: result = %d, \n\t unoptimized: predicted = %lf ns, actual = %lf ns \n\t optimized: predicted = %lf ns, actual = %lf ns\n",
		retval, unoptPredict2, time_fib_unopt2, optPredict2, time_fib_opt2);

	double time_fib_unopt3 =
		measure_function1(fibonacci_unoptimized, target + 3, &retval);
	double time_fib_opt3 =
		measure_function1(fibonacci_optimized, target + 3, &retval);
	printf
	("measuring Fibonacci number #18: result = %d, \n\t unoptimized: predicted = %lf ns, actual = %lf ns \n\t optimized: predicted = %lf ns, actual = %lf ns\n",
		retval, unoptPredict3, time_fib_unopt3, optPredict3, time_fib_opt3);

	double time_fib_unopt4 =
		measure_function1(fibonacci_unoptimized, target + 4, &retval);
	double time_fib_opt4 =
		measure_function1(fibonacci_optimized, target + 4, &retval);
	printf
	("measuring Fibonacci number #19: result = %d, \n\t unoptimized: predicted = %lf ns, actual = %lf ns \n\t optimized: predicted = %lf ns, actual = %lf ns\n",
		retval, unoptPredict4, time_fib_unopt4, optPredict4, time_fib_opt4);

	double time_fib_unopt5 =
		measure_function1(fibonacci_unoptimized, target + 5, &retval);
	double time_fib_opt5 =
		measure_function1(fibonacci_optimized, target + 5, &retval);
	printf
	("measuring Fibonacci number #20: result = %d, \n\t unoptimized: predicted = %lf ns, actual = %lf ns \n\t optimized: predicted = %lf ns, actual = %lf ns\n",
		retval, unoptPredict5, time_fib_unopt5, optPredict5, time_fib_opt5);


	if (argc < 3) {
		fprintf(stderr, "Need at least two arguments to continue\n");
		exit(EXIT_FAILURE);
	}
	target = atoi(argv[2]);

	printf("\nPART 3:\n");
	double time_div_7_iter =
	    measure_function1(is_divisible_by_7_iterative, target, &retval);
	printf("%d is %s by 7 (iterative)\n", target,
	       (retval == 0 ? "not divisible" : "divisible"));
	printf("  execution time = %f ns\n", time_div_7_iter);
	double time_div_7_rec =
	    measure_function1(is_divisible_by_7_recursive, target, &retval);
	printf("%d is %s by 7 (recursive)\n", target,
	       (retval == 0 ? "not divisible" : "divisible"));
	printf("  execution time = %f ns\n", time_div_7_rec);
	double time_div_7_tail_rec =
	    measure_function1(asm_is_divisible_by_7_tail_recursive, target,
			      &retval);
	printf("%d is %s by 7 (tail recursive)\n", target,
	       (retval == 0 ? "not divisible" : "divisible"));
	printf("  execution time = %f ns\n", time_div_7_tail_rec);

	if (argc < 6) {
		fprintf(stderr, "Need at least five arguments to continue\n");
		exit(EXIT_FAILURE);
	}
	int part4_args[3];
	for (int i = 0; i < 3; i++) {
		part4_args[i] = atoi(argv[i + 3]);
	}

	printf("\nPART 4:\n");
	/* PART 4: YOUR CODE HERE */
	double actual_div7 = measure_div7_calls(part4_args);
	printf("  actual = %f ns\n", actual_div7);

	if (argc < 7) {
		fprintf(stderr, "Need at least six arguments to continue\n");
		exit(EXIT_FAILURE);
	}
	target = atoi(argv[6]);
	if ((target <= 0) || ((target & 0x7f) != 0)) {
		fprintf(stderr,
			"Sixth argument must be positive and evenly divisible by 128\n");
		exit(EXIT_FAILURE);
	}

	printf("\nPART 5:\n");
	double time_memcpy = measure_function3(memcpy, target);
	printf("memcpy (built-in): execution time = %f ns\n", time_memcpy);
	double time_memcpy_8bit = measure_function3(memcpy_8bit, target);
	printf("memcpy (8 bits at a time): execution time = %f ns\n",
	       time_memcpy_8bit);
	double time_memcpy_64bit = measure_function3(memcpy_64bit, target);
	printf("memcpy (64 bits at a time): execution time = %f ns\n",
	       time_memcpy_64bit);
	double time_memcpy_256bit =
	       measure_function3(asm_memcpy_256bit, target);
	printf("memcpy (256 bits at a time): execution time = %f ns\n",
	       time_memcpy_256bit);

	return 0;
}
