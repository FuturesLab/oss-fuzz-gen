#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a bam_plp_t
    if (size < sizeof(void*)) {
        return 0;
    }

    // Create a bam_plp_t object
    bam_plp_t plp = bam_plp_init(NULL, NULL);

    // Call the function-under-test
    bam_plp_destroy(plp);

    return 0;
}