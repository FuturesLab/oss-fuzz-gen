#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Assuming sam_hdr_t is defined somewhere in the library headers
typedef struct {
    // Dummy structure for illustration purposes
    int dummy;
} sam_hdr_t;

// Assuming this function is defined in the library
int sam_hdr_line_index(sam_hdr_t *hdr, const char *type, const char *id);

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t structure
    sam_hdr_t hdr;
    hdr.dummy = 0; // Initialize with some default value

    // Ensure we have enough data to split into two strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two non-NULL strings
    size_t half_size = size / 2;
    char *type = (char *)malloc(half_size + 1);
    char *id = (char *)malloc(size - half_size + 1);

    if (type == NULL || id == NULL) {
        free(type);
        free(id);
        return 0;
    }

    memcpy(type, data, half_size);
    type[half_size] = '\0';

    memcpy(id, data + half_size, size - half_size);
    id[size - half_size] = '\0';

    // Check for empty strings after splitting
    if (type[0] == '\0' || id[0] == '\0') {
        free(type);
        free(id);
        return 0;
    }

    // Call the function-under-test
    int result = sam_hdr_line_index(&hdr, type, id);

    // Clean up
    free(type);
    free(id);

    return 0;
}