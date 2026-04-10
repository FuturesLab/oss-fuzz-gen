#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h" // Assuming bam_mplp_t is defined here

// Remove the 'extern "C"' linkage specification for C++ compatibility
int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    bam_mplp_t mplp = bam_mplp_init(0, NULL, NULL); // Initialize with dummy values
    int maxcnt;

    // Ensure size is sufficient to extract an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an int value from data
    maxcnt = *((int *)data);

    // Call the function-under-test
    bam_mplp_set_maxcnt(mplp, maxcnt);

    // Clean up
    bam_mplp_destroy(mplp);

    return 0;
}