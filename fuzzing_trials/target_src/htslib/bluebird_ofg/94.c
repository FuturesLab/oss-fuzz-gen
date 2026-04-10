#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"
#include "/src/htslib/cram/cram.h"
#include "htslib/sam.h" // Include the sam.h header for complete type definitions

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating objects
    if (size < sizeof(hts_itr_t)) {
        return 0;
    }

    // Allocate memory for hts_itr_t
    hts_itr_t *itr = (hts_itr_t *)malloc(sizeof(hts_itr_t));

    if (itr == NULL) {
        free(itr);
        return 0;
    }

    // Initialize hts_itr_t with dummy data
    // Note: In a real-world scenario, these would be initialized with valid data
    // For fuzzing purposes, we use the provided data to fill the structures
    memcpy(itr, data, sizeof(hts_itr_t));

    // Since hts_idx_t is an incomplete type, we cannot allocate or use it directly.
    // Instead, we assume that the function under test can handle a NULL index.
    hts_idx_t *idx = NULL;

    // Call the function-under-test
    int result = hts_itr_multi_cram(idx, itr);

    // Free allocated memory
    free(itr);

    return 0;
}