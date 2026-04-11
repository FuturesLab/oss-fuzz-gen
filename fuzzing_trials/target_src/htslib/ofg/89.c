#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the tag and the int64_t value
    if (size < 3 + sizeof(int64_t)) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *bam = bam_init1();
    if (bam == NULL) {
        return 0;
    }

    // Extract the tag from the data
    char tag[3];
    memcpy(tag, data, 2);
    tag[2] = '\0';  // Null-terminate the tag

    // Extract the int64_t value from the data
    int64_t value;
    memcpy(&value, data + 2, sizeof(int64_t));

    // Call the function under test
    bam_aux_update_int(bam, tag, value);

    // Clean up
    bam_destroy1(bam);

    return 0;
}