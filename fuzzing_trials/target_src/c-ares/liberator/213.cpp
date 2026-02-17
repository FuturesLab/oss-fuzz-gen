#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 8
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 8
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


void * f048cfe61_213 (size_t) {
	return (void *)0;
}

void f74e4c226_213 (void *) {
}

void * fe56ac0be_213 (void *, size_t) {
	return (void *)0;
}


extern "C" int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	int int_s0[1];
	memset(int_s0, 0x0, sizeof(int_s0));
	int int_s1[1];
	memset(int_s1, 0x0, sizeof(int_s1));
	memcpy(int_s0, data, sizeof(int_s0));data += sizeof(int_s0);
	memcpy(int_s1, data, sizeof(int_s1));data += sizeof(int_s1);
	int_s1[0] =  ares_library_init_mem(int_s0[0], &f048cfe61_213, &f74e4c226_213, &fe56ac0be_213);

	return 0;
}