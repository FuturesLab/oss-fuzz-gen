#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h" // Assuming the function is part of the htslib library

extern int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    // Initialize a sam_hdr_t structure
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the data is null-terminated for string operations
    char *data_str = (char *)malloc(size + 1);
    if (data_str == NULL) {
        sam_hdr_destroy(header);
        return 0; // If memory allocation fails, exit early
    }
    memcpy(data_str, data, size);
    data_str[size] = '\0';

    // Call the function-under-test
    sam_hdr_add_lines(header, data_str, size);

    // Clean up
    free(data_str);
    sam_hdr_destroy(header);

    return 0;
}