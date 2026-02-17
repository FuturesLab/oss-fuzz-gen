#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 10
#define COUNTER_NUMBER 0
#define MIN_SEED_SIZE 10
const unsigned counter_size[COUNTER_NUMBER] = {  };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	unsigned short unsignedshort_s0[1];
	memset(unsignedshort_s0, 0x0, sizeof(unsignedshort_s0));
	ares_dns_rr_key_t ares_dns_rr_key_t_s0[1];
	memset(ares_dns_rr_key_t_s0, 0x0, sizeof(ares_dns_rr_key_t_s0));
	ares_dns_opt_datatype_t ares_dns_opt_datatype_t_s0[1];
	memset(ares_dns_opt_datatype_t_s0, 0x0, sizeof(ares_dns_opt_datatype_t_s0));
	memcpy(unsignedshort_s0, data, sizeof(unsignedshort_s0));data += sizeof(unsignedshort_s0);
	memcpy(ares_dns_rr_key_t_s0, data, sizeof(ares_dns_rr_key_t_s0));data += sizeof(ares_dns_rr_key_t_s0);
	memcpy(ares_dns_opt_datatype_t_s0, data, sizeof(ares_dns_opt_datatype_t_s0));data += sizeof(ares_dns_opt_datatype_t_s0);
	ares_dns_opt_datatype_t_s0[0] =  ares_dns_opt_get_datatype(ares_dns_rr_key_t_s0[0], unsignedshort_s0[0]);

	return 0;
}