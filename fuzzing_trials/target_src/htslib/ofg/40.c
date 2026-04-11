#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/bgzf.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize BGZF file for writing
    BGZF *fp = bgzf_open("/dev/null", "w");
    if (fp == NULL) {
        return 0;
    }

    // Allocate memory for bam1_t structure
    bam1_t *b = bam_init1();
    if (b == NULL) {
        bgzf_close(fp);
        return 0;
    }

    // Ensure size is sufficient to fill bam1_t structure
    if (size > sizeof(bam1_core_t)) {
        // Allocate memory for the data field
        b->data = (uint8_t *)malloc(size);
        if (b->data == NULL) {
            bam_destroy1(b);
            bgzf_close(fp);
            return 0;
        }

        // Copy data into bam1_t structure
        memcpy(b->data, data, size);

        // Properly initialize bam1_t fields
        b->core.l_qname = data[0] % 255 + 1; // Set a valid length for the query name
        b->core.n_cigar = data[1] % 10; // Random number of cigar operations
        b->core.l_qseq = data[2] % 255;  // Random sequence length
        b->core.l_extranul = 0; // No extra null bytes

        // Set the data_len to the size of the data allocated
        b->l_data = size;

        // Call the function-under-test
        bam_write1(fp, b);

        // No need to free b->data manually
    }

    // Clean up
    bam_destroy1(b);  // This will free b->data if it was allocated
    bgzf_close(fp);

    return 0;
}