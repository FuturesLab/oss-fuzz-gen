#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 4
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 4
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	ares_bool_t ares_bool_t_s0[1];
	memset(ares_bool_t_s0, 0x0, sizeof(ares_bool_t_s0));
	memcpy(ares_bool_t_s0, data, sizeof(ares_bool_t_s0));data += sizeof(ares_bool_t_s0);
	ares_bool_t_s0[0] =  ares_threadsafety();

	return 0;
}