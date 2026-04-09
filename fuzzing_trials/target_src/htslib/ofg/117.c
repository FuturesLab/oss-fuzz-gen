#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the required parameters
    if (size < sizeof(float) + 2) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *bam = bam_init1();
    if (bam == NULL) {
        return 0;
    }

    // Extract a float from the data
    float float_val;
    memcpy(&float_val, data, sizeof(float));

    // Extract a string for the tag
    char tag[3];
    memcpy(tag, data + sizeof(float), 2);
    tag[2] = '\0';  // Null-terminate the string to ensure it's a valid C-string

    // Call the function-under-test
    bam_aux_update_float(bam, tag, float_val);

    // Clean up
    bam_destroy1(bam);

    return 0;
}