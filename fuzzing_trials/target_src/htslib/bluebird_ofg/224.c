#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with htslib
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        return 0;
    }

    // Initialize a SAM header and BAM record
    sam_hdr_t *header = sam_hdr_read(hts_file);
    if (header == NULL) {
        hts_close(hts_file);
        return 0;
    }

    bam1_t *b = bam_init1();
    if (b == NULL) {
        sam_hdr_destroy(header);
        hts_close(hts_file);
        return 0;
    }

    // Call the function-under-test
    sam_read1(hts_file, header, b);

    // Clean up
    bam_destroy1(b);
    sam_hdr_destroy(header);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to sam_hdr_tid2name

    const char* ret_sam_hdr_tid2name_kaunv = sam_hdr_tid2name(header, HTS_IDX_REST);
    if (ret_sam_hdr_tid2name_kaunv == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}