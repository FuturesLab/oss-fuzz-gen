#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/sam.h>
#include <htslib/hts_defs.h>
#include <htslib/hts_log.h>  // Include for logging

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize variables for hts_itr_query function
    hts_idx_t *idx = NULL;  // Initialize to NULL as hts_idx_init is not a standard function
    hts_itr_t *itr = NULL;  // Initialize to NULL as hts_itr_init is not a standard function
    htsFile *hts_file = NULL;  // File handle for reading

    // Open a BAM file from data
    hts_file = hts_open_format("data.bam", "rb", NULL);
    if (!hts_file) {
        hts_log_error("Failed to open BAM file");
        return 0;
    }

    // Load index for the BAM file
    idx = sam_index_load(hts_file, "data.bam");
    if (!idx) {
        hts_log_error("Failed to load index");
        hts_close(hts_file);
        return 0;
    }

    // Create an iterator for the BAM file
    itr = sam_itr_queryi(idx, HTS_IDX_START, 0, 0);
    if (!itr) {
        hts_log_error("Failed to create iterator");
        hts_idx_destroy(idx);
        hts_close(hts_file);
        return 0;
    }

    // Iterate over alignments
    bam1_t *b = bam_init1();
    while (sam_itr_next(hts_file, itr, b) >= 0) {
        // Process each alignment
    }

    // Clean up
    bam_destroy1(b);
    hts_itr_destroy(itr);
    hts_idx_destroy(idx);
    hts_close(hts_file);

    return 0;
}