#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 540
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 540
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_527(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	size_t size_t_p_s0[1];
	memset(size_t_p_s0, 0x0, sizeof(size_t_p_s0));
	char char_p_cs0[512];
	memset(char_p_cs0, 0x0, sizeof(char_p_cs0));
	void *void_p_cg0[1] = { 0 };
	ares_addr ares_addr_p_s0[1];
	memset(ares_addr_p_s0, 0x0, sizeof(ares_addr_p_s0));
	memcpy(size_t_p_s0, data, sizeof(size_t_p_s0));data += sizeof(size_t_p_s0);
	memcpy(char_p_cs0, data, sizeof(char_p_cs0));data += sizeof(char_p_cs0);
	char_p_cs0[sizeof(char_p_cs0) - 1] = 0;
	memcpy(ares_addr_p_s0, data, sizeof(ares_addr_p_s0));data += sizeof(ares_addr_p_s0);
	void_p_cg0[0] = (void * ) ares_dns_pton((const char * )char_p_cs0, ares_addr_p_s0, size_t_p_s0);
	if (void_p_cg0[0] == 0) return 0;

	return 0;
}