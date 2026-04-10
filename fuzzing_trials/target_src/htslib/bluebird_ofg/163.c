#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

// Function to handle the fuzz input
int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sam_index_load

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_find_line_pos
    char* ret_bam_flag2str_xstlu = bam_flag2str(BAM_CBACK);
    if (ret_bam_flag2str_xstlu == NULL){
    	return 0;
    }

    int ret_sam_hdr_find_line_pos_kdixc = sam_hdr_find_line_pos(header, ret_bam_flag2str_xstlu, HTS_MOD_REPORT_UNCHECKED, NULL);
    if (ret_sam_hdr_find_line_pos_kdixc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_idx_t *idx = sam_index_load(hts_file, (const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!idx) {
        bam_hdr_destroy(header);

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save
        sam_idx_save(hts_file);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        remove(tmpl);
        return 0;
    }

    hts_itr_t *itr = sam_itr_queryi(idx, HTS_IDX_NOCOOR, 0, 0);
    if (!itr) {
        hts_idx_destroy(idx);
        bam_hdr_destroy(header);
        hts_close(hts_file);
        remove(tmpl);
        return 0;
    }

    // Initialize a buffer for the third parameter
    bam1_t *b = bam_init1();
    if (!b) {
        hts_itr_destroy(itr);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_itr_destroy to hts_resize_array_
        const sam_hdr_t ptivkrbf;
        memset(&ptivkrbf, 0, sizeof(ptivkrbf));
        int ret_sam_hdr_nref_byayr = sam_hdr_nref(&ptivkrbf);
        if (ret_sam_hdr_nref_byayr < 0){
        	return 0;
        }
        const uint8_t jnscikbz = 1;
        char* ret_bam_aux2Z_fjthq = bam_aux2Z(&jnscikbz);
        if (ret_bam_aux2Z_fjthq == NULL){
        	return 0;
        }

        int ret_hts_resize_array__wapqa = hts_resize_array_(BAM_CEQUAL, BAM_CSOFT_CLIP, (size_t )ret_sam_hdr_nref_byayr, (void *)"w", (void **)&itr, BAM_FPROPER_PAIR, ret_bam_aux2Z_fjthq);
        if (ret_hts_resize_array__wapqa < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

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