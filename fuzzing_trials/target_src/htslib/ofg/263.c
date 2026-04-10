#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/sam.h> // Assuming the sam_hdr_t type is defined in this header

int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0; // Return if header initialization fails
    }

    // Ensure the data size is sufficient to create non-NULL strings
    if (size < 4) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Create strings from data
    const char *str1 = (const char *)data;
    const char *str2 = (const char *)(data + 1);
    const char *str3 = (const char *)(data + 2);
    const char *str4 = (const char *)(data + 3);

    // Ensure the strings are null-terminated
    char *term_str1 = strndup(str1, size - 3);
    char *term_str2 = strndup(str2, size - 3);
    char *term_str3 = strndup(str3, size - 3);
    char *term_str4 = strndup(str4, size - 3);

    // Call the function under test
    int result = sam_hdr_remove_except(hdr, term_str1, term_str2, term_str3);

    // Clean up
    free(term_str1);
    free(term_str2);
    free(term_str3);
    free(term_str4);
    sam_hdr_destroy(hdr);

    return 0;
}