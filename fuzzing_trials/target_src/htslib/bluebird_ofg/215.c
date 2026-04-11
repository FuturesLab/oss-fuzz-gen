#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/faidx.h"
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to hts_md5_update
    hts_md5_context* ret_hts_md5_init_keutr = hts_md5_init();
    if (ret_hts_md5_init_keutr == NULL){
    	return 0;
    }
    const uint8_t wdtgqudk = size;
    int64_t ret_bam_aux2i_arlgu = bam_aux2i(&wdtgqudk);
    if (ret_bam_aux2i_arlgu < 0){
    	return 0;
    }

    hts_md5_update(ret_hts_md5_init_keutr, (const void *)file, (unsigned long )ret_bam_aux2i_arlgu);

    // End mutation: Producer.APPEND_MUTATOR

    if (fai_build(tmpl) != 0) {
        hts_close(file);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_set_fai_filename

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_set_fai_filename with hts_set_filter_expression
    hts_set_filter_expression(file, NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    hts_close(file);
    unlink(tmpl);

    return 0;
}