#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure the data is not empty and has enough size for strings
    if (size < 5) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Allocate memory for strings
    char str1[2], str2[2], str3[2], str4[2];
    kstring_t ks = {0, 0, NULL};

    // Initialize strings with non-null values
    str1[0] = data[0];
    str1[1] = '\0';
    str2[0] = data[1];
    str2[1] = '\0';
    str3[0] = data[2];
    str3[1] = '\0';
    str4[0] = data[3];
    str4[1] = '\0';

    // Call the function-under-test
    sam_hdr_find_tag_id(hdr, str1, str2, str3, str4, &ks);

    // Clean up
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}