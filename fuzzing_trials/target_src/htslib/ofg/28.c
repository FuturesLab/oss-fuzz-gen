#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h> // Include the necessary header for sam_hdr_t and kstring_t

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Ensure that the data is not empty
    if (size == 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Create a string from the data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        sam_hdr_destroy(hdr);
        return 0; // Exit if memory allocation fails
    }
    memcpy(str, data, size);
    str[size] = '\0'; // Null-terminate the string

    // Initialize a kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = 0;
    ks.s = NULL;

    // Use an arbitrary integer value for the position
    int pos = 0;

    // Call the function-under-test
    int result = sam_hdr_find_line_pos(hdr, str, pos, &ks);

    // Clean up
    free(str);
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}