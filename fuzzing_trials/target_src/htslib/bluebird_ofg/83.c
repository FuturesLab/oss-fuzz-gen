#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/kstring.h" // Include this for kstring_t

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Check if the input size is zero
    if (size == 0) {
        return 0;
    }

    // Declare and initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Attempt to parse the input data as a SAM header
    // Ensure the data is null-terminated by copying it to a new buffer
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    if (sam_hdr_add_lines(hdr, null_terminated_data, size) < 0) {
        free(null_terminated_data);
        sam_hdr_destroy(hdr);
        return 0;
    }

    const char *type = "HD";  // Example header type, can be varied
    int pos = 0;  // Example position, can be varied
    kstring_t str;
    str.l = 0;
    str.m = size;
    str.s = (char *)malloc(size + 1);

    if (str.s == NULL) {
        free(null_terminated_data);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Ensure the string is null-terminated
    memcpy(str.s, data, size);
    str.s[size] = '\0';

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sam_hdr_find_line_pos

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sam_hdr_find_line_pos
    int result = sam_hdr_find_line_pos(hdr, NULL, BAM_CREF_SKIP, &str);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(str.s);
    free(null_terminated_data);
    sam_hdr_destroy(hdr);

    return 0;
}