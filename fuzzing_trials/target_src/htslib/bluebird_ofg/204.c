#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a SAM/BAM file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using htslib
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Define index and format strings (non-NULL)
    const char *index_filename = "index.bai";
    const char *format = "bai";
    int flags = 0; // Example flag value

    // Call the function-under-test
    hts_idx_t *index = sam_index_load3(hts_file, tmpl, index_filename, flags);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_index_load3 to sam_hdr_remove_lines

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_index_load3 to hts_idx_get_meta
    int ret_sam_hdr_nref_dtorj = sam_hdr_nref(NULL);
    if (ret_sam_hdr_nref_dtorj < 0){
    	return 0;
    }

    uint8_t* ret_hts_idx_get_meta_azwsx = hts_idx_get_meta(index, (uint32_t *)&ret_sam_hdr_nref_dtorj);
    if (ret_hts_idx_get_meta_azwsx == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t* ret_sam_hdr_read_ifscx = sam_hdr_read(hts_file);
    if (ret_sam_hdr_read_ifscx == NULL){
    	return 0;
    }
    char* ret_bam_flag2str_vesak = bam_flag2str(HTS_FMT_TBI);
    if (ret_bam_flag2str_vesak == NULL){
    	return 0;
    }
    char* ret_bam_flag2str_gmpfn = bam_flag2str(64);
    if (ret_bam_flag2str_gmpfn == NULL){
    	return 0;
    }

    int ret_sam_hdr_remove_lines_crweu = sam_hdr_remove_lines(ret_sam_hdr_read_ifscx, ret_bam_flag2str_vesak, ret_bam_flag2str_gmpfn, (void *)hts_file);
    if (ret_sam_hdr_remove_lines_crweu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_close(hts_file);
    remove(tmpl);

    return 0;
}