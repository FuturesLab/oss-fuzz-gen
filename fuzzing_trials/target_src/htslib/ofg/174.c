#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Initialize kstring_t
    kstring_t ks;
    ks.l = size;
    ks.m = size + 1; // Ensure there is space for a null terminator
    ks.s = (char *)malloc(ks.m);
    if (ks.s == NULL) return 0; // Exit if memory allocation fails
    memcpy(ks.s, data, size);
    ks.s[size] = '\0'; // Null terminate the string

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        free(ks.s);
        return 0; // Exit if header initialization fails
    }

    // Initialize bam1_t
    bam1_t *b = bam_init1();
    if (b == NULL) {
        sam_hdr_destroy(hdr);
        free(ks.s);
        return 0; // Exit if bam1_t initialization fails
    }

    // Call the function-under-test
    sam_parse1(&ks, hdr, b);

    // Clean up
    bam_destroy1(b);
    sam_hdr_destroy(hdr);
    free(ks.s);

    return 0;
}