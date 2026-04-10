#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for bam1_t and bam_aux_update_str

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure there is enough data to avoid out-of-bounds access
    if (size < 6) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t bam_record;
    memset(&bam_record, 0, sizeof(bam1_t));

    // Extract parameters from the input data
    const char *tag = (const char *)data; // First two bytes for tag
    int tag_length = 2;
    if (size < tag_length + 1) { // Ensure there's at least one more byte for type
        return 0;
    }
    
    int type = data[2]; // Third byte for type
    const char *value = (const char *)(data + 3); // Remaining bytes for value
    int value_length = size - 3;

    // Ensure null-termination of strings
    char tag_buffer[3];
    memcpy(tag_buffer, tag, 2);
    tag_buffer[2] = '\0';

    // Allocate memory for the value buffer and ensure null-termination
    char *value_buffer = (char *)malloc(value_length + 1);
    if (value_buffer == NULL) {
        return 0;
    }
    memcpy(value_buffer, value, value_length);
    value_buffer[value_length] = '\0';

    // Call the function-under-test
    if (bam_aux_update_str(&bam_record, tag_buffer, value_length, value_buffer) < 0) {
        // Handle the error if bam_aux_update_str fails
        free(value_buffer);
        return 0;
    }

    // Cleanup
    free(value_buffer);

    return 0;
}