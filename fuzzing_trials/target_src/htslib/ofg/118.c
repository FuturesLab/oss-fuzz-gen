#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a float and a null-terminated string
    if (size < sizeof(float) + 1) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0;
    }

    // Extract a float value from the data
    float float_value;
    memcpy(&float_value, data, sizeof(float));

    // Extract a null-terminated string from the data
    const char *aux_tag = (const char *)(data + sizeof(float));

    // Ensure the string is null-terminated within the provided size
    size_t max_string_length = size - sizeof(float);
    char *aux_tag_copy = (char *)malloc(max_string_length + 1);
    if (aux_tag_copy == NULL) {
        bam_destroy1(bam_record);
        return 0;
    }
    strncpy(aux_tag_copy, aux_tag, max_string_length);
    aux_tag_copy[max_string_length] = '\0';

    // Call the function under test
    bam_aux_update_float(bam_record, aux_tag_copy, float_value);

    // Clean up
    free(aux_tag_copy);
    bam_destroy1(bam_record);

    return 0;
}