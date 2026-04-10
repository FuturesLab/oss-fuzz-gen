#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

// Function to handle the fuzz input
int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to sam_read1
    sam_hdr_t xhxnbuay;
    memset(&xhxnbuay, 0, sizeof(xhxnbuay));
    size_t ret_sam_hdr_length_xirxl = sam_hdr_length(&xhxnbuay);
    if (ret_sam_hdr_length_xirxl < 0){
    	return 0;
    }
    const bam1_t qtrigwyt;
    memset(&qtrigwyt, 0, sizeof(qtrigwyt));
    bam1_t* ret_bam_dup1_jqkod = bam_dup1(&qtrigwyt);
    if (ret_bam_dup1_jqkod == NULL){
    	return 0;
    }

    int ret_sam_read1_sckcu = sam_read1(hts_file, &xhxnbuay, ret_bam_dup1_jqkod);
    if (ret_sam_read1_sckcu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_read1 to hts_set_filter_expression
    const uint8_t kcxaglgf = 0;
    char ret_bam_aux2A_zsidu = bam_aux2A(&kcxaglgf);

    int ret_hts_set_filter_expression_pknwb = hts_set_filter_expression(hts_file, &ret_bam_aux2A_zsidu);
    if (ret_hts_set_filter_expression_pknwb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save
        sam_idx_save(hts_file);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_index_load to sam_itr_regions
    const char* ret_sam_hdr_str_zqqnn = sam_hdr_str(header);
    if (ret_sam_hdr_str_zqqnn == NULL){
    	return 0;
    }
    hts_reglist_t ddmgilvg;
    memset(&ddmgilvg, 0, sizeof(ddmgilvg));

    hts_itr_t* ret_sam_itr_regions_ajcbb = sam_itr_regions(idx, header, &ddmgilvg, BAM_FSECONDARY);
    if (ret_sam_itr_regions_ajcbb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_itr_t *itr = sam_itr_queryi(idx, HTS_IDX_NOCOOR, 0, 0);
    if (!itr) {
        hts_idx_destroy(idx);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_idx_destroy to sam_itr_queryi
        uint8_t* ret_bam_aux_first_ywdqi = bam_aux_first(NULL);
        if (ret_bam_aux_first_ywdqi == NULL){
        	return 0;
        }

        hts_itr_t* ret_sam_itr_queryi_trnjl = sam_itr_queryi(idx, HTS_IDX_NOCOOR, (int64_t )*ret_bam_aux_first_ywdqi, -1);
        if (ret_sam_itr_queryi_trnjl == NULL){
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save
        sam_idx_save(hts_file);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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