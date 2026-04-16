#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_hdr_destroy with sam_hdr_incr_ref
        sam_hdr_incr_ref(header);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_incr_ref to sam_hdr_remove_lines
        const uint8_t qxjepanh = 1;
        char* ret_bam_aux2Z_gixph = bam_aux2Z(&qxjepanh);
        if (ret_bam_aux2Z_gixph == NULL){
        	return 0;
        }
        char bvuwkaan[1024] = "jqgol";

        int ret_sam_hdr_remove_lines_topkv = sam_hdr_remove_lines(header, ret_bam_aux2Z_gixph, (const char *)data, bvuwkaan);
        if (ret_sam_hdr_remove_lines_topkv < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        hts_close(hts_file);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_init1 to bam_set_qname
    char* ret_bam_flag2str_llikn = bam_flag2str(BAM_FUNMAP);
    if (ret_bam_flag2str_llikn == NULL){
    	return 0;
    }

    int ret_bam_set_qname_hfpbu = bam_set_qname(b, ret_bam_flag2str_llikn);
    if (ret_bam_set_qname_hfpbu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_read1(hts_file, header, b);

    // Clean up
    bam_destroy1(b);
    sam_hdr_destroy(header);
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}