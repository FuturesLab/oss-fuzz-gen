#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

// Fuzzer function
int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to create valid inputs
    }

    // Initialize sam_hdr_t
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        return 0;
    }

    // Split the input data into two parts for the string parameters
    size_t str1_len = size / 2;
    size_t str2_len = size - str1_len;

    // Allocate memory for the strings
    char *str1 = (char *)malloc(str1_len + 1);
    char *str2 = (char *)malloc(str2_len + 1);

    if (str1 == NULL || str2 == NULL) {
        sam_hdr_destroy(header);
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0';
    memcpy(str2, data + str1_len, str2_len);
    str2[str2_len] = '\0';

    // Call the function-under-test
    sam_hdr_change_HD(header, str1, str2);

    // Clean up
    sam_hdr_destroy(header);
    free(str1);
    free(str2);

    return 0;
}