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

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
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
    }

    // Close the htsFile

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to hts_parse_region
    char* ret_bam_flag2str_enaif = bam_flag2str(BAM_CBACK);
    if (ret_bam_flag2str_enaif == NULL){
    	return 0;
    }
    int ret_hclose_lcdmc = hclose(hfile);
    if (ret_hclose_lcdmc < 0){
    	return 0;
    }
    hts_pos_t ppvmxhav = 1;

    const char* ret_hts_parse_region_aeupf = hts_parse_region(ret_bam_flag2str_enaif, NULL, &ppvmxhav, (int64_t *)&ret_hclose_lcdmc, NULL, (void *)hts_fp, BAM_USER_OWNS_DATA);
    if (ret_hts_parse_region_aeupf == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_close(hts_fp); // This will also close the underlying hFILE

    return 0;
}