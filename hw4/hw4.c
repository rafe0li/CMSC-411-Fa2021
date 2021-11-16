/* YOUR FILE-HEADER COMMENT HERE */

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

	/* YOUR PART 2 CODE HERE */
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

	/* YOUR PART 2 CODE HERE */
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

	/* YOUR PART 2 CODE HERE */
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

	/* YOUR PART 2 CODE HERE */
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

	/* YOUR PART 1 CODE HERE */

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