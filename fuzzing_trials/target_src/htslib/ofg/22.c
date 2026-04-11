#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize bam1_t structure
    bam1_t *b = bam_init1();
    if (!b) return 0; // Exit if initialization fails

    // Allocate memory for the data to be copied
    uint8_t *aux_data = (uint8_t *)malloc(size);
    if (!aux_data) {
        bam_destroy1(b);
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data into aux_data
    memcpy(aux_data, data, size);

    // Call the function-under-test
    bam_aux_del(b, aux_data);

    // Clean up
    free(aux_data);
    bam_destroy1(b);

    return 0;
}