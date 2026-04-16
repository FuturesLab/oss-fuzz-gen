#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/kstring.h"

extern int bam_plp_insertion(const bam_pileup1_t *, kstring_t *, int *);

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a bam_pileup1_t object
    if (size < sizeof(bam_pileup1_t) + 1) {  // Ensure there's at least one byte for kstring_t
        return 0;
    }

    // Create a bam_pileup1_t object
    bam_pileup1_t pileup;
    memcpy(&pileup, data, sizeof(bam_pileup1_t));

    // Create a kstring_t object
    kstring_t str;
    str.l = 0;
    str.m = size - sizeof(bam_pileup1_t);
    str.s = (char *)malloc(str.m + 1);  // Allocate an extra byte for null-termination
    if (str.s == NULL) {
        return 0;
    }
    memcpy(str.s, data + sizeof(bam_pileup1_t), str.m);
    str.s[str.m] = '\0';  // Null-terminate the string

    // Create an integer pointer
    int result = 0;
    int *result_ptr = &result;

    // Initialize the bam_pileup1_t object to prevent undefined behavior
    memset(&pileup, 0, sizeof(bam_pileup1_t));

    // Call the function-under-test
    bam_plp_insertion(&pileup, &str, result_ptr);

    // Clean up
    free(str.s);

    return 0;
}