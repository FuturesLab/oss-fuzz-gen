#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    bam1_t *bam_record = bam_init1();
    
    if (bam_record == NULL || size == 0) {
        return 0;
    }

    // Initialize bam_record's data
    bam_record->data = (uint8_t *)malloc(size);
    if (bam_record->data == NULL) {
        bam_destroy1(bam_record);
        return 0;
    }
    memcpy(bam_record->data, data, size);
    bam_record->l_data = size;  // Corrected from data_len to l_data
    bam_record->m_data = size;

    // Set core fields to non-zero values to avoid null dereferencing
    bam_record->core.l_qname = 1;  // Length of query name
    bam_record->core.n_cigar = 1;  // Number of CIGAR operations
    bam_record->core.l_qseq = 1;   // Length of query sequence

    // Call the function-under-test
    hts_pos_t end_position = bam_endpos(bam_record);

    // Clean up
    // Remove the manual free of bam_record->data as bam_destroy1 will handle it
    bam_destroy1(bam_record);

    return 0;
}