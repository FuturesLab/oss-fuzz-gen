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

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_hopen to hts_get_format

    const htsFormat* ret_hts_get_format_vdhfj = hts_get_format(hts_fp);
    if (ret_hts_get_format_vdhfj == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_get_format to sam_index_load3
    char* ret_bam_flag2str_akqsq = bam_flag2str(HTS_VERSION);
    if (ret_bam_flag2str_akqsq == NULL){
    	return 0;
    }

    hts_idx_t* ret_sam_index_load3_wwggk = sam_index_load3(hts_fp, (const char *)Data, ret_bam_flag2str_akqsq, FT_VCF);
    if (ret_sam_index_load3_wwggk == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    }

    // Close the htsFile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_flush
    hts_flush(hts_fp); // This will also close the underlying hFILE
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}