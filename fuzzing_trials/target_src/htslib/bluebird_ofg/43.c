#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h" // Correct path for bam1_t and bam_aux_update_int

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    bam1_t *bam_record;
    char tag[3];
    int64_t value;

    // Ensure the input size is sufficient to extract necessary data
    if (size < 3 + sizeof(int64_t)) {
        return 0;
    }

    // Allocate memory for bam1_t structure
    bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0;
    }

    // Initialize the tag from the input data
    memcpy(tag, data, 2);
    tag[2] = '\0'; // Null-terminate the tag string

    // Extract the int64_t value from the input data
    memcpy(&value, data + 2, sizeof(int64_t));

    // Call the function-under-test
    bam_aux_update_int(bam_record, tag, value);

    // Clean up
    bam_destroy1(bam_record);

    return 0;
}