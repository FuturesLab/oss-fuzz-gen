#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and copy data into it
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0'; // Null-terminate the string

    // Create a dummy sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        free(str);
        return 0;
    }

    // Call the function-under-test
    int result = sam_hdr_count_lines(hdr, str);

    // Clean up
    sam_hdr_destroy(hdr);
    free(str);

    return 0;
}