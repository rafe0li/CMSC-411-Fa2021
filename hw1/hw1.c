/* 
* @author Rafael Li (rafaell1@umbc.edu)
* @hw1.c
* Program that displays information about data types,
* displays some of those values, and calculates how many 
* days are in a specified calendar month/year.
* 
* 
* 
* SIGNEDNESS OF DIFFERENT DATA TYPES
* char - Unsigned
* short - Signed
* int - Signed
* long - Signed
* long long - Signed
* size_t - Unsigned
* ssize_t - Signed
* ptrdiff_t - Signed
* 
* https://stackoverflow.com/questions/18112281/formula-to-determine-the-range-of-signed-and-unsigned-data-types-c 
* Formula for a signed num with n bits using two's complement
*
* https://downloads.ti.com/docs/esd/SPNU151S/data-types-stdz0555922.html
* Data type information
*
* https://stackoverflow.com/questions/12175358/c-size-t-and-ssize-t-negative-value/46711111
* ssize_t format specifier
* 
* https://en.wikibooks.org/wiki/C_Programming/stdint.h#:~:text=h%20is%20a%20header%20file,for%20each%20type%2C%20using%20macros%20.
* C library for intptr and uintptr is stdint.h
* 
* https://stackoverflow.com/questions/3597743/where-is-ptrdiff-t-defined-in-c
* C library for ptrdiff is stddef.h
* 
* https://www.tutorialspoint.com/c_standard_library/c_function_pow.htm
* C power function
* 
* https://stackoverflow.com/questions/4264127/correct-format-specifier-for-double-in-printf
* printf("%lf")
*/

#include <stdio.h>
#include <stdlib.h>

/* my imports */
#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/**
 * Calculates how many days are in the given month, also based upon if
 * this a leap year or not.
 *
 * If the month number is invalid, return -1
 *
 * @param[in] month_num Month number, where 1 is January, 12 is December
 * @param[in] is_leap_year Non-zero if this is a leap year, only
 * relevant for February (month number is 2)
 * @return Days in month
 */
extern int month_calc(int month_num, int is_leap_year);

int main(int argc, char *argv[])
{

	/* Prints number of bytes needed to store
	*  various data types
	*/

	char c;
	short s;
	int i;
	long l;
	long long ll;
	float f;
	double d;

	printf("BYTES NEEDED TO STORE C99 VARIABLE TYPES: \n\n");

	printf("Bool: %zu byte[s]\n", sizeof(_Bool));
	printf("Char: %zu byte[s]\n", sizeof(c));
	printf("Short: %zu byte[s]\n", sizeof(s));
	printf("Int: %zu byte[s]\n", sizeof(i));
	printf("Long: %zu byte[s]\n", sizeof(l));
	printf("Long Long: %zu byte[s]\n", sizeof(ll));
	printf("Float: %zu byte[s]\n", sizeof(f));
	printf("Double: %zu byte[s]\n\n", sizeof(d));

	/* Prints number of bytes needed to store
	*  rarer data types
	*/
	
	printf("BYTES NEEDED TO STORE RARER TYPES: \n\n");

	void* vPtr;
	size_t sz;
	ssize_t ssz;
	intptr_t iPtr(void* iEmpty);
	uintptr_t uiPtr(void* uiEmpty);
	ptrdiff_t dPtr;

	printf("void* ptr: %zu byte[s]\n", sizeof(vPtr));
	printf("size_t: %zu byte[s]\n", sizeof(sz));
	printf("ssize_t: %zu byte[s]\n", sizeof(ssz));
	printf("intptr_t: %zu byte[s]\n", sizeof(iPtr));
	printf("uintptr_t: %zu byte[s]\n", sizeof(uiPtr));
	printf("ptrdiff_t: %zu byte[s]\n\n", sizeof(dPtr));
	
	/* Calculates and prints min/max values of signed 
	*  data types
	*  Min = -1 * 2^(n-1)
	*  Max = 2^(n-1) - 1
	*/
	

	printf("MAX MIN VALS OF SIGNED DATA TYPES \n\n");

	double min;
	double max;
	double x = 0;
	double y = 0;

	/* 8 bits in signed char in C
	* min = (-1) * pow(2, (8 - 1));
	* max = pow(2, (8 - 1)) - 1;
	*
	* pow from math.h is power function in C
	*/
	min = (-1) * pow(2, (8 - 1));
	max = pow(2, (8 - 1)) - 1;

	printf("Signed char -- Max: %lf   Min: %lf\n", min, max);

	/* 16 bits in signed short*/

	printf("Signed short -- Max: %lf   Min: %lf\n", min, max);

	/* 32 bits in signed long*/
	min = (-1) * pow(2, (32 - 1));
	max = pow(2, (32 - 1)) - 1;

	printf("Signed long -- Max: %lf   Min: %lf\n", min, max);

	/* 32 bits in signed long*/
	min = (-1) * pow(2, (64 - 1));
	max = pow(2, (64 - 1)) - 1;

	printf("Signed long long -- Max: %lf   Min: %lf\n\n", min, max);


	printf("MAX MIN VALS OF UNSIGNED DATA TYPES \n\n");

	/* Calculates and prints max values of unsigned
	*  data types*/

	/* 8 bits in unsigned char*/
	min = (-1) * pow(2, (8 - 1));
	max = pow(2, (8 - 1)) - 1;

	printf("Unsigned char -- Max: %lf   Min: %lf\n", min, max);

	/* 16 bits in unsigned short*/
	min = (-1) * pow(2, (16 - 1));
	max = pow(2, (16 - 1)) - 1;

	printf("Unsigned short -- Max: %lf   Min: %lf\n", min, max);

	/* 32 bits in unsigned int*/
	min = (-1) * pow(2, (8 - 1));
	max = pow(2, (8 - 1)) - 1;

	printf("Unsigned int -- Max: %lf   Min: %lf\n", min, max);

	/* 32 bits in unsigned long*/
	min = (-1) * pow(2, (32 - 1));
	max = pow(2, (32 - 1)) - 1;

	printf("Signed Char -- Max: %lf   Min: %lf\n", min, max);

	/* 64 bits in unsigned long long*/
	min = (-1) * pow(2, (64 - 1));
	max = pow(2, (64 - 1)) - 1;

	printf("Signed Char -- Max: %lf   Min: %lf\n\n\n", min, max);


	if (argc < 3) {
		fprintf(stderr, "Need a month number and year.\n");
		exit(EXIT_FAILURE);
	} else {
		int month_num = atoi(argv[1]);
		int year = atoi(argv[2]);
		int is_leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
		printf("Number of days for month %d, year %d is: %d\n", month_num, year, month_calc(month_num, is_leap_year));
	}
	return 0;
}
