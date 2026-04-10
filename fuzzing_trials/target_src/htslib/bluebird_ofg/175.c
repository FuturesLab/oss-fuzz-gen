#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function under test
void bam_plp_set_maxcnt(bam_plp_t plp, int maxcnt);

int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a bam_plp_t object using the actual function from the library
    bam_plp_t plp = bam_plp_init(NULL, NULL);

    // Extract an integer from the data
    int maxcnt = *((int *)data);

    // Call the function under test
    bam_plp_set_maxcnt(plp, maxcnt);

    // Clean up
    bam_plp_destroy(plp);

    return 0;
}

#ifdef __cplusplus
}
#endif