#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "htslib/sam.h"
#include "htslib/hts.h"
#include <stdlib.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    ssize_t written = write(fd, data, size);
    if (written != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile in binary mode
    htsFile *hts_file = hts_open(tmpl, "rb");
    if (!hts_file) {
        unlink(tmpl);
        return 0;
    }

    // Check if the file is a valid SAM/BAM/CRAM file
    bam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    // Create a secondary index filename for testing
    char index_filename[] = "/tmp/fuzzindexXXXXXX";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to hts_resize_array_
    int ret_hts_flush_fizls = hts_flush(hts_file);
    if (ret_hts_flush_fizls < 0){
    	return 0;
    }
    char* ret_bam_flag2str_ymooa = bam_flag2str(FT_VCF);
    if (ret_bam_flag2str_ymooa == NULL){
    	return 0;
    }
    char* ret_bam_flag2str_apjug = bam_flag2str(BAM_CINS);
    if (ret_bam_flag2str_apjug == NULL){
    	return 0;
    }

    int ret_hts_resize_array__pmtob = hts_resize_array_(HTS_PATH_SEPARATOR_STR, (size_t )ret_hts_flush_fizls, HTS_IDX_NOCOOR, (void *)ret_bam_flag2str_ymooa, (void **)&header, 0, ret_bam_flag2str_apjug);
    if (ret_hts_resize_array__pmtob < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int index_fd = mkstemp(index_filename);
    if (index_fd == -1) {
        bam_hdr_destroy(header);
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }
    close(index_fd);

    // Ensure the index filename is removed if not needed
    unlink(index_filename);

    // Call the function-under-test
    hts_idx_t *index = sam_index_load2(hts_file, tmpl, index_filename);

    // Check if the index was created successfully
    if (index) {
        hts_idx_destroy(index);
    }

    // Clean up
    bam_hdr_destroy(header);
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}