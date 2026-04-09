#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Assuming sam_hdr_t is a structure defined in the relevant library
typedef struct {
    char *header;
    size_t length;
} sam_hdr_t;

// Mock function to simulate sam_hdr_length
size_t sam_hdr_length_2(sam_hdr_t *hdr) {
    if (hdr == NULL || hdr->header == NULL) {
        return 0;
    }
    return hdr->length;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Allocate memory for sam_hdr_t
    sam_hdr_t *hdr = (sam_hdr_t *)malloc(sizeof(sam_hdr_t));
    if (hdr == NULL) {
        return 0;
    }

    // Allocate memory for the header string
    hdr->header = (char *)malloc(size + 1);
    if (hdr->header == NULL) {
        free(hdr);
        return 0;
    }

    // Copy the fuzz data into the header and null-terminate it
    memcpy(hdr->header, data, size);
    hdr->header[size] = '\0';

    // Set the length of the header
    hdr->length = size;

    // Call the function-under-test
    size_t result = sam_hdr_length_2(hdr);

    // Print the result (optional, for debugging purposes)
    printf("Header length: %zu\n", result);

    // Free allocated memory
    free(hdr->header);
    free(hdr);

    return 0;
}