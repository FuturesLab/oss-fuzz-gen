#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    bam_hdr_t *header = NULL;
    bam1_t *alignment = bam_init1();
    int result = 0;

    if (alignment == NULL) {
        return 0;
    }

    // Create a temporary file to use with hts_open
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        bam_destroy1(alignment);
        return 0;
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        bam_destroy1(alignment);
        return 0;
    }

    // Open the temporary file with hts_open
    file = hts_open(tmpl, "r");
    if (file == NULL) {
        close(fd);
        unlink(tmpl);
        bam_destroy1(alignment);
        return 0;
    }

    // Attempt to read the header and alignment from the file
    header = sam_hdr_read(file);
    if (header != NULL) {
        while (sam_read1(file, header, alignment) >= 0) {
            // Process the alignment (this is where code coverage can increase)
        }
        bam_hdr_destroy(header);
    }

    // Cleanup

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_read1 to sam_idx_init
        // Ensure dataflow is valid (i.e., non-null)
        if (!file) {
        	return 0;
        }
        const htsFormat* ret_hts_get_format_iuwml = hts_get_format(file);
        if (ret_hts_get_format_iuwml == NULL){
        	return 0;
        }
        const bam1_t loptyquw;
        memset(&loptyquw, 0, sizeof(loptyquw));
        hts_pos_t ret_bam_endpos_bniab = bam_endpos(&loptyquw);
        if (ret_bam_endpos_bniab < 0){
        	return 0;
        }
        char* ret_bam_flag2str_ullzb = bam_flag2str(HTS_IDX_REST);
        if (ret_bam_flag2str_ullzb == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!file) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!header) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_flag2str_ullzb) {
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to sam_hdr_count_lines

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to sam_index_build2
        const htsFormat wujbwmhr;
        memset(&wujbwmhr, 0, sizeof(wujbwmhr));
        char* ret_hts_format_description_gjfwi = hts_format_description(&wujbwmhr);
        if (ret_hts_format_description_gjfwi == NULL){
        	return 0;
        }
        unsigned int ret_hts_features_rjxbq = hts_features();
        if (ret_hts_features_rjxbq < 0){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_hts_format_description_gjfwi) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_flag2str_ullzb) {
        	return 0;
        }
        int ret_sam_index_build2_sbztq = sam_index_build2(ret_hts_format_description_gjfwi, ret_bam_flag2str_ullzb, (int )ret_hts_features_rjxbq);
        if (ret_sam_index_build2_sbztq < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        sam_hdr_t* ret_sam_hdr_init_ffeul = sam_hdr_init();
        if (ret_sam_hdr_init_ffeul == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_sam_hdr_init_ffeul) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_flag2str_ullzb) {
        	return 0;
        }
        int ret_sam_hdr_count_lines_xjzyt = sam_hdr_count_lines(ret_sam_hdr_init_ffeul, ret_bam_flag2str_ullzb);
        if (ret_sam_hdr_count_lines_xjzyt < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        int ret_sam_idx_init_wddrx = sam_idx_init(file, header, (int )ret_bam_endpos_bniab, ret_bam_flag2str_ullzb);
        if (ret_sam_idx_init_wddrx < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save
    sam_idx_save(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
    close(fd);
    unlink(tmpl);
    bam_destroy1(alignment);

    return result;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_118(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
