#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for the function
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "HD";  // Example header type, non-NULL
    const char *key = "VN";   // Example key, non-NULL

    // Check if the size is sufficient to create a valid header
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            sam_hdr_destroy(hdr);
            return 0;
        }

        // Copy the input data to the temporary buffer and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';

        // Add the data to the header
        if (sam_hdr_add_lines(hdr, temp_data, size) < 0) {
            free(temp_data);
            sam_hdr_destroy(hdr);
            return 0;
        }

        free(temp_data);
    }

    // Call the function-under-test
    int result = sam_hdr_line_index(hdr, type, key);

    // Clean up
    sam_hdr_destroy(hdr);

    return 0;
}