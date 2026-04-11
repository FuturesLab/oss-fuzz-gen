#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_hdr_name2tid
    char* ret_bam_flag2str_awbks = bam_flag2str(0);
    if (ret_bam_flag2str_awbks == NULL){
    	return 0;
    }

    int ret_sam_hdr_name2tid_vhomq = sam_hdr_name2tid(header, ret_bam_flag2str_awbks);
    if (ret_sam_hdr_name2tid_vhomq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    bam1_t *alignment = bam_init1();
    if (!alignment) {
        sam_hdr_destroy(header);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to sam_hdr_remove_tag_id
        char* ret_bam_flag2str_ibvnl = bam_flag2str(FT_STDIN);
        if (ret_bam_flag2str_ibvnl == NULL){
        	return 0;
        }
        char* ret_bam_flag2str_iyaje = bam_flag2str(HTS_RESIZE_CLEAR);
        if (ret_bam_flag2str_iyaje == NULL){
        	return 0;
        }
        const uint8_t jhmnklkg = 64;
        char* ret_bam_aux2Z_ldpxq = bam_aux2Z(&jhmnklkg);
        if (ret_bam_aux2Z_ldpxq == NULL){
        	return 0;
        }
        hts_free((void *)hts_file);

        int ret_sam_hdr_remove_tag_id_yyqqq = sam_hdr_remove_tag_id(header, ret_bam_flag2str_ibvnl, ret_bam_flag2str_iyaje, ret_bam_aux2Z_ldpxq, hts_file);
        if (ret_sam_hdr_remove_tag_id_yyqqq < 0){
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