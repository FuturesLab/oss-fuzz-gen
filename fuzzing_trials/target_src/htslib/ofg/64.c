#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Declare and initialize variables for bam_set1 function parameters
    bam1_t *b = bam_init1();
    size_t l_data = size > 0 ? size : 1;  // Ensure non-zero size
    const char *qname = "query_name";
    uint16_t flag = 0;
    int32_t rname = 0;
    hts_pos_t pos = 0;
    uint8_t mapq = 0;
    size_t n_cigar = 1;
    uint32_t cigar_data[1] = {0};
    int32_t rnext = 0;
    hts_pos_t pnext = 0;
    hts_pos_t tlen = 0;
    size_t l_seq = 1;
    const char *seq = "A";
    const char *qual = "!";
    size_t l_aux = 0;

    // Call the function-under-test
    bam_set1(b, l_data, qname, flag, rname, pos, mapq, n_cigar, cigar_data, rnext, pnext, tlen, l_seq, seq, qual, l_aux);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_64(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
