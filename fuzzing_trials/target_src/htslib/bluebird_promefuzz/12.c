#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "htslib/hfile.h"
#include "htslib/sam.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Open a file stream using hopen

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hopen
    const char mrjvvofh[1024] = "tsmty";
    hFILE *hfile = hopen("./dummy_file", mrjvvofh);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!hfile) {
        return 0;
    }

    // Open a htsFile using hts_hopen

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hopen to hgetdelim
    char* ret_bam_flag2str_aeogi = bam_flag2str(-1);
    if (ret_bam_flag2str_aeogi == NULL){
    	return 0;
    }

    ssize_t ret_hgetdelim_cdwob = hgetdelim(ret_bam_flag2str_aeogi, BAM_FREVERSE, BAM_FREAD1, hfile);

    // End mutation: Producer.APPEND_MUTATOR

    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header
    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    }

    // Close the htsFile

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_count_lines
    const uint8_t hervkuau = 0;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_aux2Z
    const uint8_t tzmohqrl = Size;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_line_index
    char* ret_bam_flag2str_pqqot = bam_flag2str(HTS_FMT_TBI);
    if (ret_bam_flag2str_pqqot == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to hts_readlist
    int ret_bam_str2flag_hqjgx = bam_str2flag(ret_bam_flag2str_aeogi);
    if (ret_bam_str2flag_hqjgx < 0){
    	return 0;
    }
    int zidefpam = 1;

    char** ret_hts_readlist_zhsaj = hts_readlist(ret_bam_flag2str_aeogi, ret_bam_str2flag_hqjgx, &zidefpam);
    if (ret_hts_readlist_zhsaj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_readlist to sam_itr_queryi
    const uint8_t brlhaqfb = 64;
    uint32_t ret_bam_auxB_len_gkrav = bam_auxB_len(&brlhaqfb);
    if (ret_bam_auxB_len_gkrav < 0){
    	return 0;
    }

    hts_itr_t* ret_sam_itr_queryi_lhdmd = sam_itr_queryi(NULL, (int )ret_bam_auxB_len_gkrav, (int64_t )zidefpam, BAM_CSOFT_CLIP);
    if (ret_sam_itr_queryi_lhdmd == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_free((void *)hts_fp);

    int ret_sam_hdr_line_index_xduvr = sam_hdr_line_index(header, ret_bam_flag2str_pqqot, hts_fp);
    if (ret_sam_hdr_line_index_xduvr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    char* ret_bam_aux2Z_zgbfo = bam_aux2Z(&tzmohqrl);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bam_aux2Z_zgbfo == NULL){
    	return 0;
    }

    int ret_sam_hdr_count_lines_utrml = sam_hdr_count_lines(header, ret_bam_aux2Z_zgbfo);
    if (ret_sam_hdr_count_lines_utrml < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}