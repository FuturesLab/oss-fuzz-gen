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

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to bam_aux_update_str
    bam1_t oioaqcsf;
    memset(&oioaqcsf, 0, sizeof(oioaqcsf));
    const char jfuaekxu[1024] = "avaga";

    int ret_bam_aux_update_str_klnsk = bam_aux_update_str(&oioaqcsf, jfuaekxu, BAM_FPAIRED, ret_bam_flag2str_aeogi);
    if (ret_bam_aux_update_str_klnsk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ssize_t ret_hgetdelim_cdwob = hgetdelim(ret_bam_flag2str_aeogi, BAM_FREVERSE, BAM_FREAD1, hfile);

    // End mutation: Producer.APPEND_MUTATOR

    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_set_cache_size

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_set_filter_expression
    char* ret_bam_flag2str_uxtun = bam_flag2str(HTS_IDX_SILENT_FAIL);
    if (ret_bam_flag2str_uxtun == NULL){
    	return 0;
    }

    int ret_hts_set_filter_expression_cvuud = hts_set_filter_expression(hts_fp, ret_bam_flag2str_uxtun);
    if (ret_hts_set_filter_expression_cvuud < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_hfile_has_plugin_svvri = hfile_has_plugin(ret_bam_flag2str_aeogi);
    if (ret_hfile_has_plugin_svvri < 0){
    	return 0;
    }

    hts_set_cache_size(hts_fp, ret_hfile_has_plugin_svvri);

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_hdr_destroy with sam_hdr_incr_ref
        sam_hdr_incr_ref(header);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Close the htsFile

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_count_lines
    const uint8_t hervkuau = 0;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_aux2Z
    const uint8_t tzmohqrl = Size;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_line_index

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to hts_free

    hts_free((void *)header);

    // End mutation: Producer.APPEND_MUTATOR

    char* ret_bam_flag2str_pqqot = bam_flag2str(HTS_FMT_TBI);
    if (ret_bam_flag2str_pqqot == NULL){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to hts_reglist_create
    int dyoymcig = 0;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to hts_hopen

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to hts_parse_reg
    const uint8_t ksbuuhec = 0;
    double ret_bam_aux2f_aaxgb = bam_aux2f(&ksbuuhec);
    if (ret_bam_aux2f_aaxgb < 0){
    	return 0;
    }
    int flvorwqw = 64;

    const char* ret_hts_parse_reg_stihl = hts_parse_reg(ret_bam_flag2str_aeogi, &flvorwqw, (int *)&ret_bam_aux2f_aaxgb);
    if (ret_hts_parse_reg_stihl == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_hflush_ggjwz = hflush(hfile);
    if (ret_hflush_ggjwz < 0){
    	return 0;
    }

    htsFile* ret_hts_hopen_nyiaj = hts_hopen(hfile, (const char *)"r", ret_bam_flag2str_aeogi);
    if (ret_hts_hopen_nyiaj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_reglist_t* ret_hts_reglist_create_dpdix = hts_reglist_create(&ret_bam_flag2str_aeogi, HTS_MOD_REPORT_UNCHECKED, &dyoymcig, (void *)hfile, NULL);
    if (ret_hts_reglist_create_dpdix == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_free((void *)hts_fp);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_free to sam_hdr_remove_line_id
    sam_hdr_t* ret_sam_hdr_get_lumdl = sam_hdr_get(NULL);
    if (ret_sam_hdr_get_lumdl == NULL){
    	return 0;
    }
    char* ret_hts_format_description_vsqya = hts_format_description(NULL);
    if (ret_hts_format_description_vsqya == NULL){
    	return 0;
    }
    char* ret_bam_aux2Z_hrdpb = bam_aux2Z((const uint8_t *)&dyoymcig);
    if (ret_bam_aux2Z_hrdpb == NULL){
    	return 0;
    }

    int ret_sam_hdr_remove_line_id_rpxpq = sam_hdr_remove_line_id(ret_sam_hdr_get_lumdl, hts_fp, ret_hts_format_description_vsqya, ret_bam_aux2Z_hrdpb);
    if (ret_sam_hdr_remove_line_id_rpxpq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sam_hdr_line_index_xduvr = sam_hdr_line_index(header, ret_bam_flag2str_pqqot, hts_fp);
    if (ret_sam_hdr_line_index_xduvr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_aux2Z
    const uint8_t osubnzzt = -1;
    char* ret_bam_aux2Z_zgbfo = bam_aux2Z(&osubnzzt);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bam_aux2Z_zgbfo == NULL){
    	return 0;
    }

    int ret_sam_hdr_count_lines_utrml = sam_hdr_count_lines(header, ret_bam_aux2Z_zgbfo);
    if (ret_sam_hdr_count_lines_utrml < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_check_EOF
    hts_check_EOF(hts_fp); // This will also close the underlying hFILE
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}