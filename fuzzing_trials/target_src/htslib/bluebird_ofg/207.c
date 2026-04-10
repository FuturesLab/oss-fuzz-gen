#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Added for close() and unlink()
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h"

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1, fd2;
    FILE *file1, *file2;
    hts_idx_t *index = NULL;

    if (size < 2) {
        return 0;
    }

    fd1 = mkstemp(tmpl1);
    if (fd1 == -1) {
        return 0;
    }

    fd2 = mkstemp(tmpl2);
    if (fd2 == -1) {
        close(fd1);
        unlink(tmpl1);
        return 0;
    }

    file1 = fdopen(fd1, "wb");
    file2 = fdopen(fd2, "wb");

    if (file1 == NULL || file2 == NULL) {
        close(fd1);
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    fwrite(data, 1, size / 2, file1);
    fwrite(data + size / 2, 1, size - size / 2, file2);

    fclose(file1);
    fclose(file2);

    index = hts_idx_load2(tmpl1, tmpl2);

    if (index != NULL) {
        hts_idx_destroy(index);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_idx_load2 to sam_itr_queryi
    const uint8_t kmncuapa = 0;
    double ret_bam_aux2f_wfqdt = bam_aux2f(&kmncuapa);
    if (ret_bam_aux2f_wfqdt < 0){
    	return 0;
    }
    const uint8_t hqnbxnkd = 0;
    uint32_t ret_bam_auxB_len_geatb = bam_auxB_len(&hqnbxnkd);
    if (ret_bam_auxB_len_geatb < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sam_itr_queryi

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_auxB_len to bam_mods_query_type
    const uint8_t fznoghkf = 1;
    int64_t ret_bam_aux2i_xtkcx = bam_aux2i(&fznoghkf);
    if (ret_bam_aux2i_xtkcx < 0){
    	return 0;
    }
    const uint8_t msccaenw = 0;
    char* ret_bam_aux2Z_kdoin = bam_aux2Z(&msccaenw);
    if (ret_bam_aux2Z_kdoin == NULL){
    	return 0;
    }

    int ret_bam_mods_query_type_kwymo = bam_mods_query_type(NULL, HTS_PATH_SEPARATOR_CHAR, (int *)&ret_bam_auxB_len_geatb, (int *)&ret_bam_aux2i_xtkcx, ret_bam_aux2Z_kdoin);
    if (ret_bam_mods_query_type_kwymo < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_mods_query_type to hts_idx_load
    char* ret_bam_flag2str_lgytc = bam_flag2str(HTS_IDX_SAVE_REMOTE);
    if (ret_bam_flag2str_lgytc == NULL){
    	return 0;
    }

    hts_idx_t* ret_hts_idx_load_wwgfd = hts_idx_load(ret_bam_flag2str_lgytc, &ret_bam_aux2i_xtkcx);
    if (ret_hts_idx_load_wwgfd == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_itr_t* ret_sam_itr_queryi_ozfyq = sam_itr_queryi(index, HTS_RESIZE_CLEAR, HTS_IDX_NOCOOR, (int64_t)ret_bam_auxB_len_geatb);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_sam_itr_queryi_ozfyq == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}