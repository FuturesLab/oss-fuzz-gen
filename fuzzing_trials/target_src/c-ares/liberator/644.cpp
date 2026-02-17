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


extern "C" int LLVMFuzzerTestOneInput_644(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	ares_dns_rr_key_t ares_dns_rr_key_t_s0[1];
	memset(ares_dns_rr_key_t_s0, 0x0, sizeof(ares_dns_rr_key_t_s0));
	char *char_p_cg0[1] = { 0 };
	memcpy(ares_dns_rr_key_t_s0, data, sizeof(ares_dns_rr_key_t_s0));data += sizeof(ares_dns_rr_key_t_s0);
	char_p_cg0[0] = (char * ) ares_dns_rr_key_tostr(ares_dns_rr_key_t_s0[0]);
	if (char_p_cg0[0] == 0) return 0;

	return 0;
}