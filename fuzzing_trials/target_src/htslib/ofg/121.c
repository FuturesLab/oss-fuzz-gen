#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htslib/sam.h" // Assuming the function is part of the htslib library

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a meaningful input
    if (size < 2) {
        return 0;
    }

    // Create a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0; // Return if header initialization fails
    }

    // Allocate memory for the string input
    char *str = (char *)malloc(size + 1);
    if (!str) {
        sam_hdr_destroy(hdr);
        return 0; // Return if memory allocation fails
    }

    // Copy the data into the string and null-terminate it
    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test
    int result = sam_hdr_count_lines(hdr, str);

    // Clean up
    free(str);
    sam_hdr_destroy(hdr);

    return 0;
}