#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Create a temporary file to use with hts_open
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

    // Open the temporary file with hts_open
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_open to hts_crc32
    const uint8_t qkkrfhdp = size;
    uint32_t ret_bam_auxB_len_xgrby = bam_auxB_len(&qkkrfhdp);
    if (ret_bam_auxB_len_xgrby < 0){
    	return 0;
    }
    const uint8_t uvwtohqj = 1;
    uint32_t ret_bam_auxB_len_xzudm = bam_auxB_len(&uvwtohqj);
    if (ret_bam_auxB_len_xzudm < 0){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!file) {
    	return 0;
    }
    uint32_t ret_hts_crc32_ddzoi = hts_crc32(ret_bam_auxB_len_xgrby, (const void *)file, (size_t )ret_bam_auxB_len_xzudm);
    if (ret_hts_crc32_ddzoi < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    hts_flush(file);

    // Close the file
    hts_close(file);

    // Remove the temporary file
    remove(tmpl);

    return 0;
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

    LLVMFuzzerTestOneInput_98(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
