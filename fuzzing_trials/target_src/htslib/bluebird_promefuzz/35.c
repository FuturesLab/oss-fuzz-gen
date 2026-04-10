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

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hclose with hflush
        hflush(hfile); // Close hFILE only if hts_hopen fails
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0;
    }

    // Read SAM/BAM/CRAM header
    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {
        sam_hdr_destroy(header);
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to hts_parse_region
        char* ret_bam_flag2str_qrtmn = bam_flag2str(HTS_VERSION);
        if (ret_bam_flag2str_qrtmn == NULL){
        	return 0;
        }
        unsigned int ret_hts_features_jaatt = hts_features();
        if (ret_hts_features_jaatt < 0){
        	return 0;
        }
        int rnfolhac = 1;
        hts_pos_t soiukwgs = -1;
        hts_pos_t sawrwhup = 1;

        const char* ret_hts_parse_region_hortp = hts_parse_region(ret_bam_flag2str_qrtmn, &rnfolhac, &soiukwgs, &sawrwhup, NULL, (void *)header, (int )ret_hts_features_jaatt);
        if (ret_hts_parse_region_hortp == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

}

    // Close the htsFile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_check_EOF
    hts_check_EOF(hts_fp); // This will also close the underlying hFILE
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}