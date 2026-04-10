#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and size is reasonable for the header
    if (size > 0 && size < 65536) {
        // Copy the input data to a null-terminated string
        char *header_data = (char *)malloc(size + 1);
        if (header_data == NULL) {
            return 0;
        }
        memcpy(header_data, data, size);
        header_data[size] = '\0';

        // Parse the header data
        sam_hdr_t *hdr = sam_hdr_parse(size, header_data);
        if (hdr != NULL) {
            // Call the function-under-test
            const char *result = sam_hdr_str(hdr);

            // Print the result to ensure it's not NULL
            if (result != NULL) {
                printf("Header String: %s\n", result);
            }

            // Clean up
            sam_hdr_destroy(hdr);
        }

        // Free the allocated header data
        free(header_data);
    }

    return 0;
}