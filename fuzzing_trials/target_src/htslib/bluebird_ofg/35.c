#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/sam.h"
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
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
        const uint8_t nadmdnac = 64;
        char ret_bam_aux2A_croxm = bam_aux2A(&nadmdnac);
        char* ret_bam_flag2str_wftud = bam_flag2str(HTS_IDX_START);
        if (ret_bam_flag2str_wftud == NULL){
        	return 0;
        }
        char zpdzmmkj[1024] = "zhewi";
        hts_free(zpdzmmkj);
        const uint8_t irkhcjxp = size;
        char ret_bam_aux2A_grhzz = bam_aux2A(&irkhcjxp);

        int ret_sam_hdr_remove_tag_id_rnvod = sam_hdr_remove_tag_id(header, &ret_bam_aux2A_croxm, ret_bam_flag2str_wftud, (const char *)zpdzmmkj, &ret_bam_aux2A_grhzz);
        if (ret_sam_hdr_remove_tag_id_rnvod < 0){
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