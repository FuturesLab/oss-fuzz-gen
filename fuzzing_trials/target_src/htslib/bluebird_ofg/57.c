#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (!hts_file) {
        unlink(tmpl);
        return 0;
    }

    // Initialize the sam_hdr_t and bam1_t structures

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to hts_set_filter_expression
    char* ret_bam_flag2str_rzgcd = bam_flag2str(BAM_CPAD);
    if (ret_bam_flag2str_rzgcd == NULL){
    	return 0;
    }

    int ret_hts_set_filter_expression_drwkn = hts_set_filter_expression(hts_file, ret_bam_flag2str_rzgcd);
    if (ret_hts_set_filter_expression_drwkn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sam_hdr_t *header = sam_hdr_read(hts_file);
    if (!header) {
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    bam1_t *alignment = bam_init1();
    if (!alignment) {
        sam_hdr_destroy(header);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to sam_hdr_remove_tag_id

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_flag2str
        char* ret_bam_flag2str_lgzwu = bam_flag2str(BAM_CDEL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bam_flag2str_lgzwu == NULL){
        	return 0;
        }
        hts_free((void *)header);
        const uint8_t eczmdvxv = 1;
        char ret_bam_aux2A_dfqxh = bam_aux2A(&eczmdvxv);

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_flag2str
        char* ret_bam_flag2str_frtmt = bam_flag2str(BAM_CDEL);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bam_flag2str_frtmt == NULL){
        	return 0;
        }

        int ret_sam_hdr_remove_tag_id_olkqj = sam_hdr_remove_tag_id(header, ret_bam_flag2str_lgzwu, header, &ret_bam_aux2A_dfqxh, ret_bam_flag2str_frtmt);
        if (ret_sam_hdr_remove_tag_id_olkqj < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_read1(hts_file, header, alignment);

    // Clean up
    bam_destroy1(alignment);
    sam_hdr_destroy(header);
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}