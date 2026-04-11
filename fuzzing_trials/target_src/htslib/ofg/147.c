#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h"  // Correct path for bam1_t and related functions

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Initialize two bam1_t structures
    bam1_t *dest = bam_init1();
    bam1_t *src = bam_init1();

    if (dest == NULL || src == NULL) {
        if (dest != NULL) bam_destroy1(dest);
        if (src != NULL) bam_destroy1(src);
        return 0;
    }

    // Fill the source bam1_t with some data from the input
    // Ensure that the data field is properly allocated
    if (size > 0) {
        // Allocate memory for src->data if necessary
        if (src->m_data < size) {
            uint8_t *new_data = realloc(src->data, size);
            if (new_data == NULL) {
                bam_destroy1(dest);
                bam_destroy1(src);
                return 0;
            }
            src->data = new_data;
            src->m_data = size;
        }
        memcpy(src->data, data, size);
        src->l_data = size;
    }

    // Call the function-under-test
    bam1_t *result = bam_copy1(dest, src);

    // Ensure that the function under test is effectively invoked
    if (result == NULL) {
        // Handle the case where bam_copy1 fails
        bam_destroy1(dest);
        bam_destroy1(src);
        return 0;
    }

    // Clean up
    bam_destroy1(dest);
    bam_destroy1(src);
    if (result != dest) {
        bam_destroy1(result);
    }

    return 0;
}