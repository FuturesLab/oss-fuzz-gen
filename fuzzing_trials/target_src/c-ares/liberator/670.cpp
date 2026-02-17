#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 10764
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 10764
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_670(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	hostent *hostent_pp_g0[1][2] = { 0 };
	int int_p_s0[1];
	memset(int_p_s0, 0x0, sizeof(int_p_s0));
	unsigned char unsignedchar_p_cs0[512];
	memset(unsignedchar_p_cs0, 0x0, sizeof(unsignedchar_p_cs0));
	int int_s0[1];
	memset(int_s0, 0x0, sizeof(int_s0));
	int int_s1[1];
	memset(int_s1, 0x0, sizeof(int_s1));
	ares_addr6ttl ares_addr6ttl_p_s0[512];
	memset(ares_addr6ttl_p_s0, 0x0, sizeof(ares_addr6ttl_p_s0));
	memcpy(int_p_s0, data, sizeof(int_p_s0));data += sizeof(int_p_s0);
	memcpy(unsignedchar_p_cs0, data, sizeof(unsignedchar_p_cs0));data += sizeof(unsignedchar_p_cs0);
	unsignedchar_p_cs0[sizeof(unsignedchar_p_cs0) - 1] = 0;
	memcpy(int_s0, data, sizeof(int_s0));data += sizeof(int_s0);
	memcpy(int_s1, data, sizeof(int_s1));data += sizeof(int_s1);
	memcpy(ares_addr6ttl_p_s0, data, sizeof(ares_addr6ttl_p_s0));data += sizeof(ares_addr6ttl_p_s0);
	int_s1[0] =  ares_parse_aaaa_reply((const unsigned char * )unsignedchar_p_cs0, int_s0[0], hostent_pp_g0[0], ares_addr6ttl_p_s0, int_p_s0);

	return 0;
}