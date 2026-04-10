#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

// Function to handle the fuzz input
int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_read1
    sam_hdr_t* ret_sam_hdr_init_zwbra = sam_hdr_init();
    if (ret_sam_hdr_init_zwbra == NULL){
    	return 0;
    }
    bam1_t* ret_bam_init1_ipjdn = bam_init1();
    if (ret_bam_init1_ipjdn == NULL){
    	return 0;
    }

    int ret_sam_read1_oesmo = sam_read1(hts_file, ret_sam_hdr_init_zwbra, ret_bam_init1_ipjdn);
    if (ret_sam_read1_oesmo < 0){
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_idx_destroy to hts_idx_save_as
        const uint8_t rtkqtdma = 0;
        char ret_bam_aux2A_qtmim = bam_aux2A(&rtkqtdma);
        hts_free((void *)hts_file);


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_free to bam_aux_update_str
        bam1_t* ret_bam_init1_hbcow = bam_init1();
        if (ret_bam_init1_hbcow == NULL){
        	return 0;
        }
        const uint8_t rwherzqx = 64;
        char* ret_bam_aux2Z_rhhnx = bam_aux2Z(&rwherzqx);
        if (ret_bam_aux2Z_rhhnx == NULL){
        	return 0;
        }


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of bam_aux_update_str
        const char hebzexbs[1024] = "btjxa";
        int ret_bam_aux_update_str_jwgzk = bam_aux_update_str(ret_bam_init1_hbcow, hebzexbs, BAM_FREAD1, ret_bam_aux2Z_rhhnx);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bam_aux_update_str_jwgzk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_hts_idx_save_as_vovri = hts_idx_save_as(idx, &ret_bam_aux2A_qtmim, hts_file, HTS_IDX_SILENT_FAIL);
        if (ret_hts_idx_save_as_vovri < 0){
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