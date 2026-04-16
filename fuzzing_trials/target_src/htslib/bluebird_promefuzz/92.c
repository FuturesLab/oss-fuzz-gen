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

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    // Open a file stream using hopen
    hFILE *hfile = hopen("./dummy_file", "r");
    if (!hfile) {
        return 0;
    }

    // Open a htsFile using hts_hopen
    htsFile *hts_fp = hts_hopen(hfile, "./dummy_file", "r");
    if (!hts_fp) {
        hclose(hfile); // Close hFILE only if hts_hopen fails
        return 0;
    }

    // Read SAM/BAM/CRAM header

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to sam_index_load
    const htsFormat uiuuuupd;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hclose

    int ret_hclose_ppnrf = hclose(hfile);
    if (ret_hclose_ppnrf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hclose to hfile_list_schemes
    char* ret_bam_flag2str_pgkql = bam_flag2str(ret_hclose_ppnrf);
    if (ret_bam_flag2str_pgkql == NULL){
    	return 0;
    }

    int ret_hfile_list_schemes_kosus = hfile_list_schemes(ret_bam_flag2str_pgkql, (const char **)Data, &ret_hclose_ppnrf);
    if (ret_hfile_list_schemes_kosus < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    memset(&uiuuuupd, 0, sizeof(uiuuuupd));
    char* ret_hts_format_description_yvays = hts_format_description(&uiuuuupd);
    if (ret_hts_format_description_yvays == NULL){
    	return 0;
    }

    hts_idx_t* ret_sam_index_load_oatfq = sam_index_load(hts_fp, ret_hts_format_description_yvays);
    if (ret_sam_index_load_oatfq == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to hpeek

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to hts_itr_multi_next
        sam_hdr_t* ret_sam_hdr_get_vrbsq = sam_hdr_get(hts_fp);
        if (ret_sam_hdr_get_vrbsq == NULL){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_get to sam_hdr_str

        const char* ret_sam_hdr_str_qcwaf = sam_hdr_str(ret_sam_hdr_get_vrbsq);
        if (ret_sam_hdr_str_qcwaf == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_hts_itr_multi_next_apbmw = hts_itr_multi_next(hts_fp, NULL, (void *)header);
        if (ret_hts_itr_multi_next_apbmw < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        hclose_abruptly(hfile);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hclose_abruptly to hseek


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of hseek
        off_t ret_hseek_cbneh = hseek(hfile, 0, BAM_FDUP);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // End mutation: Producer.APPEND_MUTATOR

        int ret_hts_idx_nseq_cfftc = hts_idx_nseq(NULL);
        if (ret_hts_idx_nseq_cfftc < 0){
        	return 0;
        }

        ssize_t ret_hpeek_zikqo = hpeek(hfile, (void *)header, (size_t )ret_hts_idx_nseq_cfftc);

        // End mutation: Producer.APPEND_MUTATOR

}

    // Close the htsFile
    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}