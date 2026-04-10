#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "htslib/sam.h"  // Correct header file for bam1_t and bam_aux_append

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Define and initialize variables
    bam1_t *bam_record = bam_init1();
    const char *tag = "XX";  // Example tag, must be 2 characters
    char type = 'A';  // Example type, could be 'A', 'i', 'f', etc.
    int len = (size > 0) ? (int)size : 1;  // Length of data, ensure it's at least 1
    const uint8_t *value = data;  // Use the input data as the value

    // Ensure bam_record is not NULL
    if (bam_record == NULL) {
        return 0;
    }

    // Check if the input data is valid for the specified type
    if (type == 'A' && len != 1) {
        bam_destroy1(bam_record);
        return 0;
    }

    // Call the function-under-test
    int result = bam_aux_append(bam_record, tag, type, len, value);

    // Check the result of the function call
    if (result < 0) {
        fprintf(stderr, "bam_aux_append failed\n");
    }

    // Clean up
    bam_destroy1(bam_record);

    return 0;
}