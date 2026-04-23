#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the required parameters
    if (size < 100) {
        return 0;
    }

    // Initialize variables for bam_set1 parameters
    bam1_t *b = bam_init1();
    size_t l_data = size / 2;
    const char *qname = (const char *)data;
    uint16_t flag = (uint16_t)data[0];
    int32_t tid = (int32_t)data[1];
    hts_pos_t pos = (hts_pos_t)data[2];
    uint8_t mapq = data[3];
    size_t n_cigar = 1;
    uint32_t cigar[1] = {0};
    int32_t mtid = (int32_t)data[4];
    hts_pos_t mpos = (hts_pos_t)data[5];
    hts_pos_t isize = (hts_pos_t)data[6];
    size_t l_seq = size / 4;
    const char *seq = (const char *)(data + 10);
    const char *qual = (const char *)(data + 20);
    size_t l_aux = size / 8;

    // Call the function-under-test
    int result = bam_set1(b, l_data, qname, flag, tid, pos, mapq, n_cigar, cigar, mtid, mpos, isize, l_seq, seq, qual, l_aux);

    // Clean up
    bam_destroy1(b);

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

    LLVMFuzzerTestOneInput_115(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
