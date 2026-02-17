#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 520
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 520
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_549(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	ares_srv_reply *ares_srv_reply_pp_h0[1][2] = { 0 };
	ares_srv_reply *ares_srv_reply_pp_h0_shadow[1][2] = { 0 };
	int int_s0[1];
	memset(int_s0, 0x0, sizeof(int_s0));
	unsigned char unsignedchar_p_cs0[512];
	memset(unsignedchar_p_cs0, 0x0, sizeof(unsignedchar_p_cs0));
	int int_s1[1];
	memset(int_s1, 0x0, sizeof(int_s1));
	memcpy(int_s0, data, sizeof(int_s0));data += sizeof(int_s0);
	memcpy(unsignedchar_p_cs0, data, sizeof(unsignedchar_p_cs0));data += sizeof(unsignedchar_p_cs0);
	unsignedchar_p_cs0[sizeof(unsignedchar_p_cs0) - 1] = 0;
	memcpy(int_s1, data, sizeof(int_s1));data += sizeof(int_s1);
	int_s1[0] =  ares_parse_srv_reply((const unsigned char * )unsignedchar_p_cs0, int_s0[0], ares_srv_reply_pp_h0[0]);

clean_up:
	//clean dbl array
	for (uint i = 0; i < 1; i++)  if (ares_srv_reply_pp_h0_shadow[0][i] != 0 ) free(ares_srv_reply_pp_h0_shadow[0][i]);


	return 0;
}