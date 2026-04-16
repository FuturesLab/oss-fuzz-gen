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

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
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
        
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hclose to sam_hdr_remove_lines
        const sam_hdr_t glrlxtov;
        memset(&glrlxtov, 0, sizeof(glrlxtov));
        sam_hdr_t* ret_sam_hdr_dup_itkwb = sam_hdr_dup(&glrlxtov);
        if (ret_sam_hdr_dup_itkwb == NULL){
        	return 0;
        }
        char* ret_bam_flag2str_wgbmn = bam_flag2str(BAM_FREAD1);
        if (ret_bam_flag2str_wgbmn == NULL){
        	return 0;
        }

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_flag2str
        char* ret_bam_flag2str_hllgb = bam_flag2str(FT_BCF);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bam_flag2str_hllgb == NULL){
        	return 0;
        }

        int ret_sam_hdr_remove_lines_rtpah = sam_hdr_remove_lines(ret_sam_hdr_dup_itkwb, ret_bam_flag2str_wgbmn, ret_bam_flag2str_hllgb, (void *)hfile);
        if (ret_sam_hdr_remove_lines_rtpah < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

return 0;
    }

    // Read SAM/BAM/CRAM header
    sam_hdr_t *header = sam_hdr_read(hts_fp);
    if (header) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_hdr_destroy with sam_hdr_incr_ref
        sam_hdr_incr_ref(header);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Close the htsFile
    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}