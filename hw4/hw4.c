/*@author Rafael Li, rafaell1@umbc.edu
* @hw4.c
*/

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Given an ULNAv2 instruction, determine if that instruction should
 * set the CondUpdate control signal or not.
 * @param[in] inst 16-bit instruction to decode
 * @return @c true if CondUpdate is set, @c false otherwise
 */
static bool signal_condupdate(uint16_t inst)
{
	bool A = (inst >> 15) & 1;
	bool B = (inst >> 14) & 1;
	bool C = (inst >> 13) & 1;
	bool D = (inst >> 12) & 1;
	bool E = (inst >> 11) & 1;

	printf("\nINST: %d%d%d%d%d\n", A, B, C, D, E);

	if (A == 0 && B == 0 && C == 0 && D == 0) {
		return true;
	}

	if (A == 0 && B == 0 && C == 0 && D == 1 && E == 0) {
		return true;
	}

	if (A == 0 && B == 1 && D == 0 && E == 1) {
		return true;
	}

	if (A == 1 && B == 0 && C == 0 && E == 0) {
		return true;
	}

	if (B == 0 && C == 1 && D == 0 && E == 1) {
		return true;
	}

	return false;
}

/**
 * Given an ULNAv2 instruction, determine if that instruction should
 * set the MemRead control signal or not.
 * @param[in] inst 16-bit instruction to decode
 * @return @c true if MemRead is set, @c false otherwise
 */
static bool signal_memread(uint16_t inst)
{
	bool A = (inst >> 15) & 1;
	bool B = (inst >> 14) & 1;
	bool C = (inst >> 13) & 1;
	bool D = (inst >> 12) & 1;
	bool E = (inst >> 11) & 1;

	if (A == 0 && C == 1 && D == 1 && E == 1) {
		return true;
	}

	return false;
}

/**
 * Given an ULNAv2 instruction, determine if that instruction should
 * set the MemWrite control signal or not.
 * @param[in] inst 16-bit instruction to decode
 * @return @c true if MemWrite is set, @c false otherwise
 */
static bool signal_memwrite(uint16_t inst)
{
	bool A = (inst >> 15) & 1;
	bool B = (inst >> 14) & 1;
	bool C = (inst >> 13) & 1;
	bool D = (inst >> 12) & 1;
	bool E = (inst >> 11) & 1;

	if (A == 0 && C == 0 && D == 1 && E == 1) {
		return true;
	}

	if (A == 1 && B == 1 && C == 1 && D == 1 && E == 1) {
		return true;
	}

	return false;
}

/**
 * Given an ULNAv2 instruction, determine if that instruction should
 * set the RegWrite control signal or not.
 * @param[in] inst 16-bit instruction to decode
 * @return @c true if RegWrite is set, @c false otherwise
 */
static bool signal_regwrite(uint16_t inst)
{
	bool A = (inst >> 15) & 1;
	bool B = (inst >> 14) & 1;
	bool C = (inst >> 13) & 1;
	bool D = (inst >> 12) & 1;
	bool E = (inst >> 11) & 1;

	if (A == 0 && B == 0 && C == 0 && D == 0) {
		return true;
	}

	if (A == 0 && B == 0 && C == 0 && D == 1 && E == 0) {
		return true;
	}

	if (A == 0 && B == 1 && D == 0 && E == 1) {
		return true;
	}

	if (A == 1 && B == 0 && C == 0 && E == 0) {
		return true;
	}

	if (A == 0 && B == 1 && C == 0 && E == 0) {
		return true;
	}

	if (A == 0 && B == 1 && C == 1 && D == 0 && E == 1) {
		return true;
	}

	if (A == 0 && B == 1 && C == 1 && D == 1 && E == 0) {
		return true;
	}

	if (A == 1 && B == 0 && C == 1 && D == 1) {
		return true;
	}

	if (A == 1 && B == 0 && C == 1 && D == 0 && E == 0) {
		return true;
	}

	if (A == 0 && C == 0 && D == 1 && E == 1) {
		return true;
	}

	if (A == 0 && C == 1 && D == 1 && E == 1) {
		return true;
	}

	return false;
}

/**
 * Given a 16-bit value represeting an ULNAv2 instruction, disassemble
 * and describe what it does:
 *
 *  -# name of the instruction
 *  -# control signals that should be emitted by the instruction decoder
 *
 * @param[in] inst 16-bit instruction to decode
 */
static void disassemble(uint16_t inst)
{
	unsigned inst_class = (inst >> 14) & 0x3;
	char inst_class_type = 'A' + inst_class;
	printf("%04" PRIx16 ": instruction class \"%c\"\n", inst,
	       inst_class_type);

	// Isolate top 5 bits, represents instruction number
	inst = (inst << 5) | (inst >> (16 - 5));
	unsigned inst_num = inst & 0x1f;

	// Print instruct based on instruct number

	printf("this is: ");

	if (!(inst_num ^ 0)) {
		printf("or");
	}

	if (!(inst_num ^ 1)) {
		printf("add");
	}

	if (!(inst_num ^ 2)) {
		printf("and");
	}

	if (!(inst_num ^ 3)) {
		printf("stw");
	}

	if (!(inst_num ^ 4)) {
		printf("br");
	}

	if (!(inst_num ^ 5)) {
		printf("cmp");
	}

	if (!(inst_num ^ 6)) {
		printf("undef - 06");
	}

	if (!(inst_num ^ 7)) {
		printf("ldw");
	}

	if (!(inst_num ^ 8)) {
		printf("ash");
	}

	if (!(inst_num ^ 9)) {
		printf("addi");
	}

	if (!(inst_num ^ 10)) {
		printf("lsh");
	}

	if (!(inst_num ^ 11)) {
		printf("stwi");
	}

	if (!(inst_num ^ 12)) {
		printf("negi");
	}

	if (!(inst_num ^ 13)) {
		printf("brl");
	}

	if (!(inst_num ^ 14)) {
		printf("rot");
	}

	if (!(inst_num ^ 15)) {
		printf("ldwi");
	}

	if (!(inst_num ^ 16)) {
		printf("ori");
	}

	if (!(inst_num ^ 17)) {
		printf("undef - 17");
	}

	if (!(inst_num ^ 18)) {
		printf("andi");
	}

	if (!(inst_num ^ 19)) {
		printf("undef - 19");
	}

	if (!(inst_num ^ 20)) {
		printf("movi");
	}

	if (!(inst_num ^ 21)) {
		printf("cmpi");
	}

	if (!(inst_num ^ 22)) {
		printf("movis");
	}

	if (!(inst_num ^ 23)) {
		printf("bl");
	}

	if (!(inst_num ^ 24)) {
		printf("b");
	}

	if (!(inst_num ^ 25)) {
		printf("b.gt");
	}

	if (!(inst_num ^ 26)) {
		printf("b.eq");
	}

	if (!(inst_num ^ 27)) {
		printf("b.ge");
	}

	if (!(inst_num ^ 28)) {
		printf("b.lt");
	}

	if (!(inst_num ^ 29)) {
		printf("b.ne");
	}

	if (!(inst_num ^ 30)) {
		printf("b.le");
	}

	if (!(inst_num ^ 31)) {
		printf("halt");
	}

	printf("\n");

	printf("      CondUpdate: %d\n", (signal_condupdate(inst) ? 1 : 0));
	printf("      MemRead: %d\n", (signal_memread(inst) ? 1 : 0));
	printf("      MemWrite: %d\n", (signal_memwrite(inst) ? 1 : 0));
	printf("      RegWrite: %d\n", (signal_regwrite(inst) ? 1 : 0));
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE.IMG\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *f = fopen(argv[1], "r");
	if (!f) {
		fprintf(stderr, "Failed to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	char buf[255];
	fgets(buf, sizeof(buf), f);
	while (1) {
		if (fgets(buf, sizeof(buf), f) == NULL)
			break;
		unsigned long val = strtoul(buf, NULL, 16);
		disassemble((uint16_t) val);
	}
	return 0;
}