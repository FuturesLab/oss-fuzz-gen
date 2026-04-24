#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_read to sam_write1
    htsFile oofffgmk;
    memset(&oofffgmk, 0, sizeof(oofffgmk));
    const htsFormat* ret_hts_get_format_yixcf = hts_get_format(&oofffgmk);
    if (ret_hts_get_format_yixcf == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!alignment) {
    	return 0;
    }
    bam1_t* ret_bam_dup1_pzihi = bam_dup1(alignment);
    if (ret_bam_dup1_pzihi == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!header) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_bam_dup1_pzihi) {
    	return 0;
    }
    int ret_sam_write1_eojjn = sam_write1(&oofffgmk, header, ret_bam_dup1_pzihi);
    if (ret_sam_write1_eojjn < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    hts_close(file);
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

    LLVMFuzzerTestOneInput_97(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
