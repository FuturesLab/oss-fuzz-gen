#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
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
        char* ret_bam_flag2str_ejlnq = bam_flag2str(64);
        if (ret_bam_flag2str_ejlnq == NULL){
        	return 0;
        }
        const uint8_t rfhkztgk = 1;
        char ret_bam_aux2A_hogri = bam_aux2A(&rfhkztgk);
        hts_free((void *)hts_file);
        char* ret_bam_flag2str_dwhim = bam_flag2str(1);
        if (ret_bam_flag2str_dwhim == NULL){
        	return 0;
        }

        int ret_sam_hdr_remove_tag_id_xvcgk = sam_hdr_remove_tag_id(header, ret_bam_flag2str_ejlnq, &ret_bam_aux2A_hogri, hts_file, ret_bam_flag2str_dwhim);
        if (ret_sam_hdr_remove_tag_id_xvcgk < 0){
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