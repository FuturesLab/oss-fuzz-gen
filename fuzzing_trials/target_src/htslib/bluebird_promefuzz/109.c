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

int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
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
    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to hts_md5_update
        hts_md5_context* ret_hts_md5_init_mimrt = hts_md5_init();
        if (ret_hts_md5_init_mimrt == NULL){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_md5_init to hts_md5_update
        sam_hdr_t* ret_sam_hdr_get_wbdaf = sam_hdr_get(hts_fp);
        if (ret_sam_hdr_get_wbdaf == NULL){
        	return 0;
        }

        hts_md5_update(ret_hts_md5_init_mimrt, (const void *)ret_sam_hdr_get_wbdaf, BAM_FREAD1);

        // End mutation: Producer.APPEND_MUTATOR

        hts_md5_update(ret_hts_md5_init_mimrt, (const void *)header, 0);

        // End mutation: Producer.APPEND_MUTATOR

}

    // Close the htsFile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_check_EOF

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_idx_init
    htsFile lzipuzux;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_line_index
    char* ret_bam_flag2str_sjdls = bam_flag2str(BAM_FMREVERSE);
    if (ret_bam_flag2str_sjdls == NULL){
    	return 0;
    }
    const uint8_t cvhcrjqj = Size;
    char ret_bam_aux2A_kqoub = bam_aux2A(&cvhcrjqj);

    int ret_sam_hdr_line_index_smqbd = sam_hdr_line_index(header, ret_bam_flag2str_sjdls, &ret_bam_aux2A_kqoub);
    if (ret_sam_hdr_line_index_smqbd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    memset(&lzipuzux, 0, sizeof(lzipuzux));
    int ret_sam_idx_save_zhzvu = sam_idx_save(&lzipuzux);
    if (ret_sam_idx_save_zhzvu < 0){
    	return 0;
    }
    hts_free((void *)hfile);

    int ret_sam_idx_init_utlmx = sam_idx_init(&lzipuzux, header, FT_BCF, hfile);
    if (ret_sam_idx_init_utlmx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_check_EOF(hts_fp); // This will also close the underlying hFILE
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}