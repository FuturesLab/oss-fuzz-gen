#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>
#include <htslib/sam.h> // Include this for sam_hdr_read and related functions
#include <stdlib.h>
#include <string.h>

// Remove the extern "C" linkage specification since this is C code, not C++
int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure that size is at least 1 to avoid empty filter expression
    if (size < 1) {
        return 0;
    }

    // Create a temporary htsFile object
    htsFile *hts_file = hts_open("-", "r");
    if (hts_file == NULL) {
        return 0;
    }

    // Create a dummy header, necessary for some operations
    bam_hdr_t *header = bam_hdr_init();
    if (header == NULL) {
        hts_close(hts_file);
        return 0;
    }

    // Allocate memory for the filter expression and copy data into it
    char *filter_expr = (char *)malloc(size + 1);
    if (filter_expr == NULL) {
        bam_hdr_destroy(header);
        hts_close(hts_file);
        return 0;
    }
    memcpy(filter_expr, data, size);
    filter_expr[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    // Ensure that the function is correctly invoked
    int result = hts_set_filter_expression(hts_file, filter_expr);
    if (result != 0) {
        // Handle error if needed
    }

    // Add a dummy read to ensure the filter expression is actually used
    bam1_t *b = bam_init1();
    if (b != NULL) {
        while (sam_read1(hts_file, header, b) >= 0) {
            // Process the read if needed
        }
        bam_destroy1(b);
    }

    // Cleanup
    free(filter_expr);
    bam_hdr_destroy(header);
    hts_close(hts_file);

    return 0;
}