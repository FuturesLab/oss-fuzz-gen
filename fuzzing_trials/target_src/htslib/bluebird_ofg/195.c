#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "/src/htslib/htslib/kstring.h"

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Initialize kstring_t
    kstring_t ks;
    ks.l = size;
    ks.m = size + 1; // Ensure there is space for a null terminator
    ks.s = (char *)malloc(ks.m);
    if (ks.s == NULL) {
        return 0;
    } // Exit if memory allocation fails
    memcpy(ks.s, data, size);
    ks.s[size] = '\0'; // Null terminate the string

    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        free(ks.s);
        return 0; // Exit if header initialization fails
    }

    // Initialize bam1_t
    bam1_t *b = bam_init1();
    if (b == NULL) {
        sam_hdr_destroy(hdr);
        free(ks.s);
        return 0; // Exit if bam1_t initialization fails
    }

    // Call the function-under-test
    sam_parse1(&ks, hdr, b);

    // Clean up
    bam_destroy1(b);
    sam_hdr_destroy(hdr);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to sam_hdr_update_line
    const uint8_t bjcqmbxp = -1;
    char* ret_bam_aux2Z_mwfoi = bam_aux2Z(&bjcqmbxp);
    if (ret_bam_aux2Z_mwfoi == NULL){
    	return 0;
    }

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_flag2str
    char* ret_bam_flag2str_nwfjm = bam_flag2str(BAM_FSUPPLEMENTARY);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bam_flag2str_nwfjm == NULL){
    	return 0;
    }
    char* ret_bam_flag2str_ndbsn = bam_flag2str(BAM_FPROPER_PAIR);
    if (ret_bam_flag2str_ndbsn == NULL){
    	return 0;
    }

    int ret_sam_hdr_update_line_pefzp = sam_hdr_update_line(hdr, ret_bam_aux2Z_mwfoi, ret_bam_flag2str_nwfjm, ret_bam_flag2str_ndbsn);
    if (ret_sam_hdr_update_line_pefzp < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(ks.s);

    return 0;
}