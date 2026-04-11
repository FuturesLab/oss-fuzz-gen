#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract meaningful data
    if (size < 3) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Use part of the input data as a string for the second parameter
    size_t str_len = size - 2;
    char *str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(str, data, str_len);
    str[str_len] = '\0';

    // Use another part of the input data as an integer for the third parameter
    int pos = (int)data[size - 1];

    // Call the function-under-test
    sam_hdr_remove_line_pos(hdr, str, pos);

    // Clean up
    free(str);
    sam_hdr_destroy(hdr);

    return 0;
}