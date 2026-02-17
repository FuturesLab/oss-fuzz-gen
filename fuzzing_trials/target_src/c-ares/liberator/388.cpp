#include <ares.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FIXED_SIZE 520
#define COUNTER_NUMBER 17
#define MIN_SEED_SIZE 652
const unsigned counter_size[COUNTER_NUMBER] = { 4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };

#define NEW_DATA_LEN 4096


#define MIN(x,y) ((x < y) ? x : y)


extern "C" int LLVMFuzzerTestOneInput_388(const uint8_t *data, size_t Size) {
	if (Size < MIN_SEED_SIZE) return 0;
	long long_p_s0[1];
	memset(long_p_s0, 0x0, sizeof(long_p_s0));
	char *char_pp_h0[1][17] = { 0 };
	char *char_pp_h0_shadow[1][17] = { 0 };
	size_t size_t_s0[1];
	memset(size_t_s0, 0x0, sizeof(size_t_s0));
	unsigned char unsignedchar_p_cs1[512];
	memset(unsignedchar_p_cs1, 0x0, sizeof(unsignedchar_p_cs1));
	int int_s0[1];
	memset(int_s0, 0x0, sizeof(int_s0));
	unsigned char *unsignedchar_p_ch0[1] = { 0 };
	unsigned char *unsignedchar_p_ch0_shadow[1] = { 0 };
	memcpy(long_p_s0, data, sizeof(long_p_s0));data += sizeof(long_p_s0);
	memcpy(unsignedchar_p_cs1, data, sizeof(unsignedchar_p_cs1));data += sizeof(unsignedchar_p_cs1);
	unsignedchar_p_cs1[sizeof(unsignedchar_p_cs1) - 1] = 0;
	//dyn array init
	memcpy(int_s0, data, sizeof(int_s0));data += sizeof(int_s0);
	unsignedchar_p_ch0[0] = (unsigned char*)malloc(int_s0[0]*sizeof(unsignedchar_p_ch0[0][0]));
	unsignedchar_p_ch0_shadow[0] = unsignedchar_p_ch0[0];
	memcpy(unsignedchar_p_ch0[0], data, int_s0[0]);
	data += int_s0[0];

	if (int_s0[0] > 0) unsignedchar_p_ch0[0][int_s0[0] - 1] = 0;
	//dyn dbl array init
	for (uint i = 0; i < 16; i++) {
		memcpy(size_t_s0, data, sizeof(size_t_s0));data += sizeof(size_t_s0);
		char_pp_h0[0][i] = (char*)malloc(size_t_s0[0]*sizeof(char_pp_h0[0][i][0]));
		char_pp_h0_shadow[0][i] = char_pp_h0[0][i];
		memcpy(char_pp_h0[0][i], data, size_t_s0[0]);
		char_pp_h0[0][i][size_t_s0[0] - 1] = 0;
		data += size_t_s0[0];
	}

	int_s0[0] =  ares_expand_name((const unsigned char * )unsignedchar_p_cs1, (const unsigned char * )unsignedchar_p_ch0[0], int_s0[0], char_pp_h0[0], long_p_s0);

clean_up:
	//clean dbl array
	for (uint i = 0; i < 16; i++)  if (char_pp_h0_shadow[0][i] != 0 ) free(char_pp_h0_shadow[0][i]);

	if (unsignedchar_p_ch0_shadow[0] != 0) free(unsignedchar_p_ch0[0]);

	return 0;
}

int cmpfunc_388 (const void * a, const void * b)
{return ( *(unsigned*)a - *(unsigned*)b );}

// Forward-declare the libFuzzer's mutator callback.
extern "C" size_t LLVMFuzzerMutate(uint8_t *Data, size_t Size, size_t MaxSize);

extern "C" size_t LLVMFuzzerCustomMutator_388(uint8_t *Data, size_t Size, size_t MaxSize, unsigned int Seed) {

	// select the field to mutate: fized or a dynamic one
	unsigned field = (unsigned)(rand() % (COUNTER_NUMBER + 1));
	// mutate the fixed part
	if (field == 0) {
		uint8_t fixed_field[FIXED_SIZE];
		memcpy(fixed_field, Data, FIXED_SIZE);
		size_t new_fixed_data = LLVMFuzzerMutate(fixed_field, FIXED_SIZE, FIXED_SIZE);

		if (new_fixed_data > FIXED_SIZE) {
			printf("[ERROR] for the fixed size, I have a longer size");
			return 1;
		}
		// LLVMFuzzerMutate could reduce the seed size
		if (new_fixed_data < FIXED_SIZE) {
			size_t to_append_size = FIXED_SIZE-new_fixed_data;
			for (unsigned i = 0; i < to_append_size; i++)
			// fixed_field[new_fixed_data+i] = (uint8_t)rand();
			fixed_field[new_fixed_data+i] = 0x0;
		}
		memcpy(Data, fixed_field, FIXED_SIZE);
		return Size;
	// mutate one of the dynamic fields
	} else {
		unsigned dyn_field_idx = field - 1;

		size_t counter = 0;
		uint8_t *counter_addr = Data + FIXED_SIZE;
		uint8_t *buffer_start, *buffer_end;
		size_t to_read = MIN(sizeof(size_t), counter_size[0]);
		memcpy(&counter, counter_addr, to_read);
		buffer_start = Data + FIXED_SIZE + counter_size[0];
		buffer_end = buffer_start + counter;
		if (dyn_field_idx != 0) {
			for (unsigned i = 1; i < COUNTER_NUMBER && i != (dyn_field_idx + 1); i++) {
				to_read = MIN(sizeof(size_t), counter_size[i]);
				memcpy(&counter, buffer_end, to_read);
				counter_addr = buffer_end;
				buffer_start = buffer_end + counter_size[i];
				buffer_end = buffer_start + counter;

			}
		}
		uint8_t dynamic_field[NEW_DATA_LEN];

		memcpy(dynamic_field, buffer_start, counter);

		size_t new_dynamic_data = LLVMFuzzerMutate(dynamic_field, counter, NEW_DATA_LEN);

		if (new_dynamic_data > NEW_DATA_LEN) {
			printf("[ERROR] for the dynamic size, I have a longer size");
			return 1;
		}

		size_t new_whole_data_size = Size - (counter - new_dynamic_data);
		if (new_whole_data_size == 0 || new_whole_data_size > MaxSize)
			return 0;

		uint8_t *new_data = (uint8_t*)malloc(new_whole_data_size);
		uint8_t *new_data_original = new_data;
		memset(new_data, 0, new_whole_data_size);

		// copy what stays before the old dyn buffer
		memcpy(new_data, Data, counter_addr - Data);
		new_data += counter_addr - Data;

		// store the new counter
		size_t real_counter_size = MIN(sizeof(size_t), counter_size[dyn_field_idx]);
		memcpy(new_data, &new_dynamic_data, real_counter_size);
		new_data += counter_size[dyn_field_idx];

		// store the new dynamic field
		memcpy(new_data, dynamic_field, new_dynamic_data);
		new_data += new_dynamic_data;

		// dynamic region is not the last one
		if (buffer_end != Data + Size && new_dynamic_data > 0) {
			size_t leftover_size = (Data + Size) - buffer_end;
			memcpy(new_data, buffer_end, leftover_size);
		}

		// re-transfer the new seed into the Data buffer
		memcpy(Data, new_data_original, new_whole_data_size);
		free(new_data_original);

		return new_whole_data_size;
	}
}
