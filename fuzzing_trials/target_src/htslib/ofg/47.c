#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h" // Include the necessary header for sam_hdr_t

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a string and an integer
    if (size < 5) return 0;

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) return 0;

    // Create a null-terminated string from the data
    size_t str_len = size - 4; // Reserve last 4 bytes for an integer
    char *str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(str, data, str_len);
    str[str_len] = '\0';

    // Extract an integer from the remaining bytes
    int idx = *(int *)(data + str_len);

    // Call the function-under-test
    const char *result = sam_hdr_line_name(hdr, str, idx);

    // Output the result for debugging purposes
    if (result != NULL) {
        printf("Result: %s\n", result);
    }

    // Clean up
    free(str);
    sam_hdr_destroy(hdr);

    return 0;
}