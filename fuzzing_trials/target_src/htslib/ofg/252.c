#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a non-empty string
    if (size == 0) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Allocate memory for the string and copy data into it
    char *lines = (char *)malloc(size + 1);
    if (lines == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(lines, data, size);
    lines[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    sam_hdr_add_lines(hdr, lines, size);

    // Clean up
    free(lines);
    sam_hdr_destroy(hdr);

    return 0;
}