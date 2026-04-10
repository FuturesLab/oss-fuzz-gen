#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htslib/sam.h" // Correct path for the header file where bam_aux_del is declared

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to perform meaningful operations
    if (size < 4) { // Ensure there is enough data to form a valid tag and some auxiliary data
        return 0;
    }

    // Allocate memory for bam1_t structure
    bam1_t *bam = bam_init1();
    if (bam == NULL) {
        return 0;
    }

    // Allocate memory for the bam data
    bam->data = (uint8_t *)malloc(size);
    if (bam->data == NULL) {
        bam_destroy1(bam);
        return 0;
    }
    memcpy(bam->data, data, size);
    bam->l_data = size;

    // Ensure bam1_t structure is properly initialized
    bam->m_data = size; // Set the maximum allocated size of the data buffer
    bam->core.l_qname = 1; // Set a valid value for the length of the query name
    bam->core.n_cigar = 0; // Set a valid value for the number of CIGAR operations
    bam->core.l_qseq = 0; // Set a valid value for the length of the sequence

    // Allocate memory for the auxiliary data pointer
    uint8_t *aux_data = (uint8_t *)malloc(size - 2); // Allocate enough space for the auxiliary data excluding the tag
    if (aux_data == NULL) {
        free(bam->data);
        bam_destroy1(bam);
        return 0;
    }
    memcpy(aux_data, data + 2, size - 2); // Copy auxiliary data, skipping the first 2 bytes (for the tag)

    // Call the function-under-test
    // Ensure that bam_aux_del is called with a valid tag
    char tag[3] = { data[0], data[1], '\0' }; // Extract a valid tag from the first two bytes of data
    int result = bam_aux_del(bam, tag);
    // Check if bam_aux_del was successful and handle accordingly
    if (result == 0) {
        // If deletion was successful, we should not free aux_data again
        aux_data = NULL;
    }

    // Clean up
    if (aux_data != NULL) {
        free(aux_data);
    }
    // Remove the double-free issue by ensuring bam->data is only freed once
    bam_destroy1(bam);

    return 0;
}