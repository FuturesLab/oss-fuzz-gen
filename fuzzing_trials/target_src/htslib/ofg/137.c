#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h> // Ensure you have htslib installed and properly linked
#include <htslib/kstring.h> // Include the kstring.h header for kstring_t

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Create a valid SAM header to ensure the function under test has something to work with
    kstring_t hdr_str = {0, 0, NULL};
    ksprintf(&hdr_str, "@HD\tVN:1.6\n@SQ\tSN:chr1\tLN:248956422\n");
    if (sam_hdr_add_lines(hdr, hdr_str.s, hdr_str.l) != 0) {
        free(hdr_str.s);
        sam_hdr_destroy(hdr);
        return 0;
    }
    free(hdr_str.s);

    const char *type = "SQ"; // Example type, can be varied
    const char *id = "SN";   // Example id, can be varied
    const char *val = "chr1"; // Example value, can be varied
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size + 1);
    if (!ks.s) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(ks.s, data, size);
    ks.s[size] = '\0';

    // Call the function-under-test
    int result = sam_hdr_find_line_id(hdr, type, id, val, &ks);

    // Cleanup
    free(ks.s);
    sam_hdr_destroy(hdr);

    return 0;
}