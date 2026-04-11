#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

// Function to handle the fuzz input
int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Check if the input size is reasonable
    if (size < 4) { // Arbitrary small size to avoid processing very small inputs
        return 0;
    }

    // Initialize htsFile with a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with htslib
    htsFile *hts_file = hts_open(tmpl, "r");
    if (!hts_file) {
        remove(tmpl);
        return 0;
    }

    // Read the header

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to sam_hdr_set
    const sam_hdr_t wqebuzqh;
    memset(&wqebuzqh, 0, sizeof(wqebuzqh));
    sam_hdr_t* ret_sam_hdr_dup_bythe = sam_hdr_dup(&wqebuzqh);
    if (ret_sam_hdr_dup_bythe == NULL){
    	return 0;
    }

    int ret_sam_hdr_set_iyfgx = sam_hdr_set(hts_file, ret_sam_hdr_dup_bythe, HTS_IDX_NOCOOR);
    if (ret_sam_hdr_set_iyfgx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Initialize an iterator

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_write1
    size_t ret_sam_hdr_length_fmtpk = sam_hdr_length(ret_sam_hdr_dup_bythe);
    if (ret_sam_hdr_length_fmtpk < 0){
    	return 0;
    }
    const bam1_t unpkofip;
    memset(&unpkofip, 0, sizeof(unpkofip));

    int ret_sam_write1_cqcdy = sam_write1(hts_file, ret_sam_hdr_dup_bythe, &unpkofip);
    if (ret_sam_write1_cqcdy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_idx_t *idx = sam_index_load(hts_file, tmpl);
    if (!idx) {
        bam_hdr_destroy(header);
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    hts_itr_t *itr = sam_itr_queryi(idx, HTS_IDX_NOCOOR, 0, 0);
    if (!itr) {
        hts_idx_destroy(idx);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_idx_destroy to sam_itr_queryi


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of sam_itr_queryi
        hts_itr_t* ret_sam_itr_queryi_eetvp = sam_itr_queryi(idx, 64, BAM_FMUNMAP, 64);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_sam_itr_queryi_eetvp == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        bam_hdr_destroy(header);
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Initialize a buffer for the third parameter
    bam1_t *b = bam_init1();
    if (!b) {
        hts_itr_destroy(itr);
        hts_idx_destroy(idx);
        bam_hdr_destroy(header);
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    while (sam_itr_next(hts_file, itr, b) >= 0) {
        // Process each record (for fuzzing, we don't need to do anything here)
    }

    // Clean up
    bam_destroy1(b);
    hts_itr_destroy(itr);
    hts_idx_destroy(idx);
    bam_hdr_destroy(header);
    hts_close(hts_file);
    remove(tmpl);

    return 0;
}