#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the structures
    if (size < sizeof(bam_hdr_t) + sizeof(bam1_t)) {
        return 0;
    }

    // Initialize bam_hdr_t
    bam_hdr_t hdr;
    memset(&hdr, 0, sizeof(bam_hdr_t));
    hdr.text = (char *)data; // Using data as a placeholder for text
    hdr.l_text = size > 0 ? 1 : 0; // Ensure non-zero length

    // Initialize bam1_t
    bam1_t b;
    memset(&b, 0, sizeof(bam1_t));
    b.data = (uint8_t *)data; // Using data as a placeholder for bam1_t data
    b.l_data = size > 0 ? 1 : 0; // Ensure non-zero length

    // Initialize kstring_t
    kstring_t str;
    memset(&str, 0, sizeof(kstring_t));
    str.s = (char *)malloc(size + 1); // Allocate memory for the string
    if (!str.s) {
        return 0; // Exit if memory allocation fails
    }
    str.l = 0;
    str.m = size + 1;

    // Call the function under test
    int result = sam_format1(&hdr, &b, &str);

    // Clean up
    free(str.s);

    return 0;
}