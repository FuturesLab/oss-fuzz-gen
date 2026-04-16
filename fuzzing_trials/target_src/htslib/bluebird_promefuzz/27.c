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

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hgetdelim

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hgetdelim
    ssize_t ret_hgetdelim_cdwob = hgetdelim(ret_bam_flag2str_aeogi, BAM_CINS, BAM_FREAD1, hfile);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_set_cache_size
    int ret_hfile_has_plugin_svvri = hfile_has_plugin(ret_bam_flag2str_aeogi);
    if (ret_hfile_has_plugin_svvri < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_set_cache_size
    hts_set_cache_size(hts_fp, FT_BCF);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_set_cache_size to sam_read1
    sam_hdr_t* ret_sam_hdr_read_ltutv = sam_hdr_read(hts_fp);
    if (ret_sam_hdr_read_ltutv == NULL){
    	return 0;
    }
    bam1_t* ret_bam_dup1_zgsur = bam_dup1(&oioaqcsf);
    if (ret_bam_dup1_zgsur == NULL){
    	return 0;
    }

    int ret_sam_read1_xnfzx = sam_read1(hts_fp, ret_sam_hdr_read_ltutv, ret_bam_dup1_zgsur);
    if (ret_sam_read1_xnfzx < 0){
    	return 0;
    }

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
    int64_t ret_bam_aux2i_qollr = bam_aux2i((const uint8_t *)&ret_hfile_has_plugin_svvri);
    if (ret_bam_aux2i_qollr < 0){
    	return 0;
    }
    const bam1_t udlhzwvz;
    memset(&udlhzwvz, 0, sizeof(udlhzwvz));
    hts_pos_t ret_bam_endpos_zobdw = bam_endpos(&udlhzwvz);
    if (ret_bam_endpos_zobdw < 0){
    	return 0;
    }

    const char* ret_hts_parse_reg_lclbv = hts_parse_reg(ret_bam_flag2str_aeogi, (int *)&ret_bam_aux2i_qollr, (int *)&ret_bam_endpos_zobdw);
    if (ret_hts_parse_reg_lclbv == NULL){
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_detect_format2
    hts_free((void *)hts_fp);
    htsFormat eyxtfudd;
    memset(&eyxtfudd, 0, sizeof(eyxtfudd));

    int ret_hts_detect_format2_wlhsb = hts_detect_format2(hfile, hts_fp, &eyxtfudd);
    if (ret_hts_detect_format2_wlhsb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_reglist_t* ret_hts_reglist_create_dpdix = hts_reglist_create(&ret_bam_flag2str_aeogi, HTS_MOD_REPORT_UNCHECKED, &dyoymcig, (void *)hfile, NULL);
    if (ret_hts_reglist_create_dpdix == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_free((void *)hts_fp);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_hdr_line_index with sam_hdr_change_HD

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_free to hfile_list_schemes
    char* ret_bam_flag2str_msqsp = bam_flag2str(HTS_IDX_NOCOOR);
    if (ret_bam_flag2str_msqsp == NULL){
    	return 0;
    }

    int ret_hfile_list_schemes_kbqez = hfile_list_schemes(header, &ret_bam_flag2str_msqsp, &ret_bam_endpos_zobdw);
    if (ret_hfile_list_schemes_kbqez < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sam_hdr_line_index_xduvr = sam_hdr_change_HD(header, ret_bam_flag2str_pqqot, hts_fp);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}