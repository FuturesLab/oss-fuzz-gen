#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to split into required strings
    if (size < 3) { // Adjusted to ensure valid memory access
        return 0;
    }

    // Initialize a SAM header
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create strings from the input data
    // Ensure the strings are null-terminated by allocating extra space
    char *null_terminated_str1 = (char *)malloc(size - 2 + 1);
    char *null_terminated_str2 = (char *)malloc(size - 1 + 1);
    char *null_terminated_str3 = (char *)malloc(size + 1);

    if (!null_terminated_str1 || !null_terminated_str2 || !null_terminated_str3) {
        free(null_terminated_str1);
        free(null_terminated_str2);
        free(null_terminated_str3);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data into strings and null-terminate them
    memcpy(null_terminated_str1, data, size - 2);
    null_terminated_str1[size - 2] = '\0';

    memcpy(null_terminated_str2, data + 1, size - 2); // Adjusted to avoid overflow
    null_terminated_str2[size - 2] = '\0';

    memcpy(null_terminated_str3, data + 2, size - 2); // Adjusted to avoid overflow
    null_terminated_str3[size - 2] = '\0';

    // Call the function under test
    sam_hdr_remove_line_id(hdr, null_terminated_str1, null_terminated_str2, null_terminated_str3);

    // Clean up
    free(null_terminated_str1);
    free(null_terminated_str2);
    free(null_terminated_str3);
    sam_hdr_destroy(hdr);

    return 0;
}