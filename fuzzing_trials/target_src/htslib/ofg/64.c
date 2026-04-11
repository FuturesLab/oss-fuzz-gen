#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h> // Include the htslib header for bam1_t

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a bam1_t structure
    if (size < sizeof(bam1_t)) {
        return 0;
    }

    // Allocate memory for bam1_t and initialize it
    bam1_t *bam_record = (bam1_t *)malloc(sizeof(bam1_t));
    if (bam_record == NULL) {
        return 0;
    }

    // Initialize bam_record fields
    bam_record->data = (uint8_t *)malloc(size);
    if (bam_record->data == NULL) {
        free(bam_record);
        return 0;
    }

    // Copy the input data to bam_record->data
    memcpy(bam_record->data, data, size);
    bam_record->l_data = size;
    bam_record->m_data = size;

    // Set other fields of bam1_t to reasonable defaults
    bam_record->core.tid = 0;
    bam_record->core.pos = 0;
    bam_record->core.bin = 0;
    bam_record->core.qual = 0;
    bam_record->core.l_qname = 1;
    bam_record->core.flag = 0;
    bam_record->core.n_cigar = 0;
    bam_record->core.l_qseq = 0;
    bam_record->core.mtid = 0;
    bam_record->core.mpos = 0;
    bam_record->core.isize = 0;

    // Call the function-under-test
    uint8_t *aux_data = bam_aux_first(bam_record);

    // Clean up
    free(bam_record->data);
    free(bam_record);

    return 0;
}