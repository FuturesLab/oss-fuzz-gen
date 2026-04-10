#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

// Function to handle the fuzz input
int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
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
    bam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Initialize an iterator
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_idx_destroy to hts_idx_save_as
        char* ret_bam_flag2str_jsafy = bam_flag2str(BAM_CEQUAL);
        if (ret_bam_flag2str_jsafy == NULL){
        	return 0;
        }
        char* ret_bam_flag2str_ihdtt = bam_flag2str(BAM_CPAD);
        if (ret_bam_flag2str_ihdtt == NULL){
        	return 0;
        }
        const uint8_t uklrmuji = 64;
        double ret_bam_aux2f_rczyx = bam_aux2f(&uklrmuji);
        if (ret_bam_aux2f_rczyx < 0){
        	return 0;
        }

        int ret_hts_idx_save_as_dvaba = hts_idx_save_as(idx, ret_bam_flag2str_jsafy, ret_bam_flag2str_ihdtt, (int )ret_bam_aux2f_rczyx);
        if (ret_hts_idx_save_as_dvaba < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_hclose_mdagy = hclose(NULL);
        if (ret_hclose_mdagy < 0){
        	return 0;
        }

        hts_itr_t* ret_sam_itr_queryi_ifaaj = sam_itr_queryi(idx, BAM_FUNMAP, BAM_CMATCH, (int64_t )ret_hclose_mdagy);
        if (ret_sam_itr_queryi_ifaaj == NULL){
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_init1 to bam_aux_remove
    int ret_hfile_has_plugin_fcuda = hfile_has_plugin(NULL);
    if (ret_hfile_has_plugin_fcuda < 0){
    	return 0;
    }

    uint8_t* ret_bam_aux_remove_wlivh = bam_aux_remove(b, (uint8_t *)&ret_hfile_has_plugin_fcuda);
    if (ret_bam_aux_remove_wlivh == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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