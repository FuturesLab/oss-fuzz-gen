#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create valid strings
    if (size < 3) {
        return 0;
    }

    // Allocate memory for sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create non-null strings for the second and third parameters
    const char *type = "SQ"; // Example string, can be varied
    const char *key = "SN";  // Example string, can be varied

    // Create a non-null pointer for the fourth parameter
    void *val = (void *)(data + 2);

    // Call the function-under-test
    int result = sam_hdr_remove_lines(hdr, type, key, val);

    // Clean up
    sam_hdr_destroy(hdr);

    return 0;
}