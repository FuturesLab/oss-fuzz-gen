#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/faidx.h"
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;
    FILE *fp;

    // Create a temporary file
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    fp = fdopen(fd, "wb");
    if (fp == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the temporary file with hts_open
    file = hts_open(tmpl, "r");
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Attempt to create an index for the file to ensure it's in a valid format

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to sam_index_load
    const htsFormat wvcfgzlq;
    memset(&wvcfgzlq, 0, sizeof(wvcfgzlq));
    char* ret_hts_format_description_viwsf = hts_format_description(&wvcfgzlq);
    if (ret_hts_format_description_viwsf == NULL){
    	return 0;
    }

    hts_idx_t* ret_sam_index_load_gwqyb = sam_index_load(file, ret_hts_format_description_viwsf);
    if (ret_sam_index_load_gwqyb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    if (fai_build(tmpl) != 0) {
        hts_close(file);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    hts_set_fai_filename(file, tmpl);

    // Clean up
    hts_close(file);
    unlink(tmpl);

    return 0;
}