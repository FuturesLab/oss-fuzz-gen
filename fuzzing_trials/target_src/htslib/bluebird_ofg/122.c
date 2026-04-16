#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/faidx.h"
#include <string.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
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
    if (fai_build(tmpl) != 0) {
        hts_close(file);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_set_fai_filename

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_set_fai_filename
    hts_set_fai_filename(file, (const char *)"w");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    hts_close(file);
    unlink(tmpl);

    return 0;
}