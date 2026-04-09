#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Initialize a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create a buffer to store the header text
    char *header_text = (char *)malloc(size + 1);
    if (header_text == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy the fuzzer data into the header text buffer
    memcpy(header_text, data, size);
    header_text[size] = '\0'; // Null-terminate the string

    // Parse the header text into the sam_hdr_t object
    if (sam_hdr_add_lines(hdr, header_text, size) < 0) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *dup_hdr = sam_hdr_dup(hdr);

    // Clean up
    free(header_text);
    sam_hdr_destroy(hdr);
    if (dup_hdr != NULL) {
        sam_hdr_destroy(dup_hdr);
    }

    return 0;
}