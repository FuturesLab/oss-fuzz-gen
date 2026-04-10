#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

// Function to simulate index creation (for fuzzing purposes)
hts_idx_t *create_dummy_index() {
    // Create a mock index object for fuzzing purposes
    // Using arbitrary values for offset0, min_shift, and n_lvls
    uint64_t offset0 = 0;
    int min_shift = 14;
    int n_lvls = 5;
    return hts_idx_init(0, HTS_FMT_CSI, offset0, min_shift, n_lvls); // Create an empty index
}

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize necessary variables
    hts_idx_t *idx = create_dummy_index();
    sam_hdr_t *hdr = sam_hdr_init();
    char *regions[1];
    unsigned int flags = 0;

    // Ensure none of the parameters are NULL
    if (!hdr || !idx) {
        if (hdr) sam_hdr_destroy(hdr);
        if (idx) hts_idx_destroy(idx);
        return 0;
    }

    // Allocate and initialize the region string
    regions[0] = (char *)malloc(size + 1);
    if (!regions[0]) {
        sam_hdr_destroy(hdr);
        hts_idx_destroy(idx);
        return 0;
    }

    // Copy data into the region string and null-terminate it
    memcpy(regions[0], data, size);
    regions[0][size] = '\0';

    // Initialize the header with a dummy sequence name
    if (sam_hdr_add_line(hdr, "SQ", "SN", "chr1", "LN", "1000", NULL) != 0) {
        free(regions[0]);
        sam_hdr_destroy(hdr);
        hts_idx_destroy(idx);
        return 0;
    }

    // Add additional dummy sequence to increase coverage
    sam_hdr_add_line(hdr, "SQ", "SN", "chr2", "LN", "2000", NULL);

    // Ensure the index is not empty by adding a dummy record
    bam1_t *b = bam_init1();
    if (b) {
        // Set a dummy record to the bam structure
        const char *qname = "dummy";
        uint32_t cigar[1] = {0};
        const char *seq = "ACGT"; // Provide a dummy sequence
        const char *qual = "!!!!"; // Provide a dummy quality string
        bam_set1(b, strlen(qname) + 1, qname, 0, 0, 0, 0, 0, cigar, -1, -1, 4, 4, seq, qual, 0);
        hts_idx_push(idx, 0, 0, 100, 0, 0);
        bam_destroy1(b);
    }

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_regarray(idx, hdr, regions, flags);

    // Clean up
    if (itr) hts_itr_destroy(itr);
    free(regions[0]);
    sam_hdr_destroy(hdr);
    hts_idx_destroy(idx);

    return 0;
}