#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;
    char *header_text = NULL;

    // Ensure the data is not empty and create a null-terminated string
    if (size > 0) {
        header_text = (char *)malloc(size + 1);
        if (header_text == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(header_text, data, size);
        header_text[size] = '\0'; // Null-terminate the string

        // Parse the header text into a sam_hdr_t structure
        hdr = sam_hdr_parse(size, header_text);
        if (hdr != NULL) {
            // Call the function-under-test
            int nref = sam_hdr_nref(hdr);
            // Print or use the result if needed
            printf("Number of reference sequences: %d\n", nref);

            // Free the header structure
            sam_hdr_destroy(hdr);
        }

        // Free the allocated header text
        free(header_text);
    }

    return 0;
}