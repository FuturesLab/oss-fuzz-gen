#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
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
        char* ret_bam_flag2str_kkpfb = bam_flag2str(BAM_CDIFF);
        if (ret_bam_flag2str_kkpfb == NULL){
        	return 0;
        }
        const htsFormat jjbdjbrq;
        memset(&jjbdjbrq, 0, sizeof(jjbdjbrq));
        char* ret_hts_format_description_llnvm = hts_format_description(&jjbdjbrq);
        if (ret_hts_format_description_llnvm == NULL){
        	return 0;
        }
        char* ret_bam_flag2str_vstxf = bam_flag2str(BAM_FREAD2);
        if (ret_bam_flag2str_vstxf == NULL){
        	return 0;
        }

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_flag2str
        char* ret_bam_flag2str_ifmop = bam_flag2str(size);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_bam_flag2str_ifmop == NULL){
        	return 0;
        }

        int ret_sam_hdr_remove_tag_id_nkfdb = sam_hdr_remove_tag_id(header, ret_bam_flag2str_kkpfb, ret_hts_format_description_llnvm, ret_bam_flag2str_vstxf, ret_bam_flag2str_ifmop);
        if (ret_sam_hdr_remove_tag_id_nkfdb < 0){
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