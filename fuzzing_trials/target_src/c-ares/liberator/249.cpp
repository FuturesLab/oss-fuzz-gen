#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 20
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 20
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	ares_addr ares_addr_p_cs0[1];
	memset(ares_addr_p_cs0, 0x0, sizeof(ares_addr_p_cs0));
	char *char_p_g0[1] = { 0 };
	memcpy(ares_addr_p_cs0, data, sizeof(ares_addr_p_cs0));data += sizeof(ares_addr_p_cs0);
	char_p_g0[0] =  ares_dns_addr_to_ptr((const ares_addr * )ares_addr_p_cs0);
	if (char_p_g0[0] == 0) return 0;

	return 0;
}