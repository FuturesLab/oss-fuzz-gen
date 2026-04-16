#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // for close() and unlink()
#include "htslib/sam.h"
#include "/src/htslib/htslib/bgzf.h"
#include <string.h>  // for strlen()

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    BGZF *bgzf = NULL;
    sam_hdr_t *sam_hdr = NULL;
    int result = 0;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;  // If we can't create a temp file, exit early
    }

    // Open the temporary file with BGZF
    bgzf = bgzf_fdopen(fd, "w");
    if (bgzf == NULL) {
        close(fd);
        return 0;
    }

    // Ensure the input data is null-terminated before passing to sam_hdr_parse
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        bgzf_close(bgzf);
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a sam_hdr_t object from the input data

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sam_hdr_parse
    sam_hdr = sam_hdr_parse(BAM_CMATCH, null_terminated_data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    free(null_terminated_data);

    if (sam_hdr == NULL) {
        bgzf_close(bgzf);
        return 0;
    }

    // Call the function-under-test
    result = bam_hdr_write(bgzf, sam_hdr);

    // Clean up
    sam_hdr_destroy(sam_hdr);
    bgzf_close(bgzf);
    unlink(tmpl);  // Remove the temporary file

    return 0;
}