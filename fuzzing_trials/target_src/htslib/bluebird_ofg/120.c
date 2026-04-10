#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to be useful
    if (size < 4) { // Updated to 4 to ensure we can set a valid tag, type, and value
        return 0;
    }

    // Allocate memory for bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0;
    }

    // Allocate memory for auxiliary data
    uint8_t *aux_data = (uint8_t *)malloc(size);
    if (aux_data == NULL) {
        bam_destroy1(bam_record);
        return 0;
    }

    // Copy the input data into the auxiliary data
    memcpy(aux_data, data, size);

    // Properly initialize the bam1_t structure
    bam_record->data = aux_data;
    bam_record->l_data = size;

    // Ensure the auxiliary data is formatted correctly
    // For example, setting a valid auxiliary tag for removal
    if (size >= 4) {
        // Set a valid tag, type, and value
        aux_data[0] = 'X';
        aux_data[1] = 'Y';
        aux_data[2] = 'Z'; // Assuming 'Z' is a valid type for the test
        aux_data[3] = 0;   // Set a value for the tag
    }

    // Call the function-under-test
    // Check if the tag exists before attempting to remove it
    if (bam_aux_get(bam_record, "XY") != NULL) {
        uint8_t *result = bam_aux_remove(bam_record, aux_data);
        (void)result; // Use result to avoid unused variable warning
    }

    // Cleanup
    // Remove the manual free of aux_data to prevent double-free
    bam_destroy1(bam_record);

    return 0;
}