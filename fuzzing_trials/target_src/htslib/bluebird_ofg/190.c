#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/kstring.h"

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for splitting into multiple parts
    if (size < 5) { // Adjusted to ensure we have enough data for type, id, pos, and tag
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Create a kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size);
    if (ks.s == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(ks.s, data, size);

    // Split data into parts for the function parameters
    const char *type = (const char *)data;
    int len_type = strnlen(type, size) + 1; // Use strnlen to avoid reading beyond buffer
    if (len_type >= size) {
        free(ks.s);
        sam_hdr_destroy(hdr);
        return 0;
    }

    const char *id = (const char *)(data + len_type);
    int len_id = strnlen(id, size - len_type) + 1; // Adjust size to remaining buffer
    if (len_type + len_id >= size) {
        free(ks.s);
        sam_hdr_destroy(hdr);
        return 0;
    }

    int pos = (int)data[len_type + len_id];
    if (len_type + len_id + 1 >= size) { // Ensure there's space for at least one char in tag
        free(ks.s);
        sam_hdr_destroy(hdr);
        return 0;
    }

    const char *tag = (const char *)(data + len_type + len_id + 1);

    // Call the function-under-test
    sam_hdr_find_tag_pos(hdr, type, pos, tag, &ks);

    // Clean up
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}