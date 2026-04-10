#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract multiple strings
    if (size < 5) {
        return 0;
    }

    // Initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Allocate space for strings and ensure null-termination
    char str1[2], str2[2], str3[2], str4[2];
    kstring_t ks = {0, 0, NULL};

    // Extract strings from data
    str1[0] = (char)data[0];
    str1[1] = '\0';
    str2[0] = (char)data[1];
    str2[1] = '\0';
    str3[0] = (char)data[2];
    str3[1] = '\0';
    str4[0] = (char)data[3];
    str4[1] = '\0';

    // Use the rest of the data for kstring_t
    ks.l = size - 4;
    ks.s = (char *)malloc(ks.l + 1);
    if (!ks.s) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(ks.s, data + 4, ks.l);
    ks.s[ks.l] = '\0';

    // Call the function-under-test
    int result = sam_hdr_find_tag_id(hdr, str1, str2, str3, str4, &ks);

    // Clean up
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}