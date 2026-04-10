#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h"

// Define a dummy function that matches the bam_plp_auto_f type
int dummy_func(void *data, const bam_pileup1_t *pl, int n) {
    return 0; // Dummy implementation
}

// Function-under-test
void bam_mplp_set_maxcnt(bam_mplp_t mplp, int maxcnt);

// Fuzzing harness
int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Prepare the arguments for bam_mplp_init
    int n = 1; // Number of data elements
    void *data_ptr = NULL; // Dummy data pointer

    // Create a bam_mplp_t object using the correct function signature
    bam_mplp_t mplp = bam_mplp_init(n, dummy_func, &data_ptr);
    if (!mplp) {
        return 0; // Failed to create bam_mplp_t object
    }

    // Use the first sizeof(int) bytes of data as an integer
    int maxcnt = *(const int *)data;

    // Call the function-under-test
    bam_mplp_set_maxcnt(mplp, maxcnt);

    // Clean up using a function from the htslib
    bam_mplp_destroy(mplp);

    return 0;
}