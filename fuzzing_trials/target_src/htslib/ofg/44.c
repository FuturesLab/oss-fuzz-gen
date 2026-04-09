#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

// Remove 'extern "C"' as it is not needed in C code
int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Call the function-under-test
    bam1_t *bam = bam_init1();

    // Check if bam is not NULL
    if (bam != NULL) {
        // Normally, you would perform operations on the bam1_t object here.
        // Since bam_init1() does not take any input, we don't use `data` or `size`.
        
        // Free the allocated bam1_t object
        bam_destroy1(bam);
    }

    return 0;
}