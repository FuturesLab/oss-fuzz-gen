#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include "htslib/sam.h" // Include additional library for hts_idx_t related operations

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for creating a valid hts_idx_t object
    if (size < 1) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    // Provide required arguments for hts_idx_init
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_BAI, 0, 14, 5); // Initialize an index object with arbitrary values
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
        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of hts_idx_push
        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of hts_idx_push
        hts_idx_push(idx, tid, BAM_CPAD, pos + 1, BAM_FQCFAIL, 1); // Provide an offset of 0 and is_mapped as 1
        // End mutation: Producer.REPLACE_ARG_MUTATOR
        // End mutation: Producer.REPLACE_ARG_MUTATOR
    }
    hts_idx_finish(idx, pos);

    // Call the function-under-test
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

    LLVMFuzzerTestOneInput_138(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
