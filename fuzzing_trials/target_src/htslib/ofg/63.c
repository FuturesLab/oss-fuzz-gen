#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

// Function-under-test
uint8_t * bam_aux_first(const bam1_t *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    if (size < sizeof(bam1_t)) {
        return 0; // Not enough data to form a bam1_t structure
    }

    // Allocate memory for bam1_t
    bam1_t *bam_record = (bam1_t *)malloc(sizeof(bam1_t));
    if (bam_record == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize bam1_t structure with the provided data
    memcpy(bam_record, data, sizeof(bam1_t));

    // Ensure auxiliary data is not NULL
    if (size > sizeof(bam1_t)) {
        bam_record->data = (uint8_t *)malloc(size - sizeof(bam1_t));
        if (bam_record->data != NULL) {
            memcpy(bam_record->data, data + sizeof(bam1_t), size - sizeof(bam1_t));
        }
    } else {
        bam_record->data = NULL;
    }

    // Call the function-under-test
    uint8_t *aux_data = bam_aux_first(bam_record);

    // Clean up
    free(bam_record->data);
    free(bam_record);

    return 0;
}