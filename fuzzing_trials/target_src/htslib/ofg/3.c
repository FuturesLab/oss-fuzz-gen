#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Assuming sam_hdr_t is defined in a relevant header file
typedef struct {
    // Mock structure for the purpose of this example
    char *header_data;
    size_t length;
} sam_hdr_t;

// Mock implementation of sam_hdr_length for demonstration
size_t sam_hdr_length_3(sam_hdr_t *hdr) {
    if (hdr == NULL || hdr->header_data == NULL) {
        return 0;
    }
    return hdr->length;
}

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Allocate memory for sam_hdr_t
    sam_hdr_t hdr;
    hdr.header_data = (char *)malloc(size + 1);
    if (hdr.header_data == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the header_data
    memcpy(hdr.header_data, data, size);
    hdr.header_data[size] = '\0'; // Null-terminate the string
    hdr.length = size;

    // Call the function-under-test
    size_t length = sam_hdr_length_3(&hdr);

    // Print the length for debugging purposes (optional)
    printf("Header length: %zu\n", length);

    // Free allocated memory
    free(hdr.header_data);

    return 0;
}