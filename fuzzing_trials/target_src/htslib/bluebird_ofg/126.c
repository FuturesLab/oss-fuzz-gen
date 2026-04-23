#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
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
        // Ensure dataflow is valid (i.e., non-null)
        if (!file) {
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bam_flag2str to hts_set_filter_expression
        // Ensure dataflow is valid (i.e., non-null)
        if (!file) {
        	return 0;
        }
        int ret_hts_flush_xdkub = hts_flush(file);
        if (ret_hts_flush_xdkub < 0){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!file) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_flag2str_ullzb) {
        	return 0;
        }
        int ret_hts_set_filter_expression_pqlpt = hts_set_filter_expression(file, ret_bam_flag2str_ullzb);
        if (ret_hts_set_filter_expression_pqlpt < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        sam_hdr_t* ret_sam_hdr_get_yigvy = sam_hdr_get(file);
        if (ret_sam_hdr_get_yigvy == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_sam_hdr_get_yigvy) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_flag2str_ullzb) {
        	return 0;
        }
        int ret_sam_hdr_count_lines_qohwg = sam_hdr_count_lines(ret_sam_hdr_get_yigvy, ret_bam_flag2str_ullzb);
        if (ret_sam_hdr_count_lines_qohwg < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        

        // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from sam_hdr_count_lines to sam_hdr_write using the plateau pool
        htsFile *hts_file = hts_open(tmpl, "wb");
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_sam_hdr_get_yigvy) {
        	return 0;
        }
        int ret_sam_hdr_write_jguqs = sam_hdr_write(hts_file, ret_sam_hdr_get_yigvy);
        if (ret_sam_hdr_write_jguqs < 0){
        	return 0;
        }
        // End mutation: Producer.SPLICE_MUTATOR
        
        int ret_sam_idx_init_wddrx = sam_idx_init(file, header, (int )ret_bam_endpos_bniab, ret_bam_flag2str_ullzb);
        if (ret_sam_idx_init_wddrx < 0){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_idx_save with hts_check_EOF
    hts_check_EOF(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
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

    LLVMFuzzerTestOneInput_126(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
