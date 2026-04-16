#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "htslib/kstring.h"

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < 4) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Prepare a dummy header string
    const char *header_text = "@HD\tVN:1.0\n";
    if (sam_hdr_add_lines(hdr, header_text, strlen(header_text)) < 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Extract parts of the input data for parameters
    const char *type = (const char *)data;
    int type_len = 2; // Assuming the type is 2 characters long
    if (size < type_len + 2) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    int id = data[type_len]; // Use the next byte as an int
    const char *tag = (const char *)(data + type_len + 1);
    int tag_len = 2; // Assuming the tag is 2 characters long
    if (size < type_len + 1 + tag_len) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = 0;
    ks.s = NULL;

    // Call the function-under-test
    int result = sam_hdr_find_tag_pos(hdr, type, id, tag, &ks);

    // Clean up
    sam_hdr_destroy(hdr);
    free(ks.s);

    return 0;
}