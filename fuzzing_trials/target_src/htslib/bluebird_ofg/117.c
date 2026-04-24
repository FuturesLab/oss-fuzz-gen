#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include "htslib/sam.h" // Include additional library for hts_idx_t related operations

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for creating a valid hts_idx_t object
    if (size < 1) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    // Provide required arguments for hts_idx_init
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_idx_init
    hts_idx_t *idx = hts_idx_init(0, FT_UNKN, 0, 14, 5); // Initialize an index object with arbitrary values
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (!idx) {
        return 0; // Failed to initialize index
    }

    int tid = 0; // Set tid to 0 for testing
    uint64_t mapped = 0; // Initialize mapped to 0
    uint64_t unmapped = 0; // Initialize unmapped to 0

    // Simulate adding data to the index to avoid using an uninitialized index
    // This is a mock operation to simulate a realistic scenario
    hts_pos_t pos = 0;
    for (size_t i = 0; i < size; ++i) {
        pos += data[i];
        // Correct the number of arguments for hts_idx_push
        hts_idx_push(idx, tid, pos, pos + 1, 0, 1); // Provide an offset of 0 and is_mapped as 1
    }
    hts_idx_finish(idx, pos);

    // Call the function-under-test

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from hts_idx_finish to hts_itr_multi_cram using the plateau pool
    hts_itr_t *itr = hts_itr_query(idx, 0, 0, 0, 0);
    // Ensure dataflow is valid (i.e., non-null)
    if (!idx) {
    	return 0;
    }
    int ret_hts_itr_multi_cram_neipx = hts_itr_multi_cram(idx, itr);
    if (ret_hts_itr_multi_cram_neipx < 0){
    	return 0;
    }
    // End mutation: Producer.SPLICE_MUTATOR
    
    int result = hts_idx_get_stat(idx, tid, &mapped, &unmapped);

    // Clean up
    hts_idx_destroy(idx);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_117(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
