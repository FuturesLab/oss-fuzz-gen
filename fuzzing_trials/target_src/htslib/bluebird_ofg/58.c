#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
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
        htsFile rwdjijmz;
        memset(&rwdjijmz, 0, sizeof(rwdjijmz));
        int ret_hts_flush_taefe = hts_flush(&rwdjijmz);
        if (ret_hts_flush_taefe < 0){
        	return 0;
        }
        sam_hdr_t gmicuopq;
        memset(&gmicuopq, 0, sizeof(gmicuopq));
        size_t ret_sam_hdr_length_wvfcj = sam_hdr_length(&gmicuopq);
        if (ret_sam_hdr_length_wvfcj < 0){
        	return 0;
        }
        const uint8_t wuctxwlf = size;
        char* ret_bam_aux2Z_hhkub = bam_aux2Z(&wuctxwlf);
        if (ret_bam_aux2Z_hhkub == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!header) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_bam_aux2Z_hhkub) {
        	return 0;
        }
        int ret_sam_idx_init_dxnoi = sam_idx_init(&rwdjijmz, header, (int )ret_sam_hdr_length_wvfcj, ret_bam_aux2Z_hhkub);
        if (ret_sam_idx_init_dxnoi < 0){
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

    LLVMFuzzerTestOneInput_58(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
