#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 0
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 0
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	ares_library_cleanup();

	return 0;
}