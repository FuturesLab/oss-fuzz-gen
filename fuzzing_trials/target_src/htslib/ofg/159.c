#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include for strdup and memcpy
#include <htslib/sam.h>
#include <htslib/kstring.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize bam_hdr_t
    bam_hdr_t hdr;
    hdr.n_targets = 1;
    hdr.target_len = (uint32_t *)malloc(sizeof(uint32_t));
    hdr.target_len[0] = 1000;
    hdr.target_name = (char **)malloc(sizeof(char *));
    hdr.target_name[0] = strdup("chr1");

    // Initialize bam1_t
    bam1_t *b = bam_init1();
    b->core.tid = 0;
    b->core.pos = 0;
    b->core.qual = 20;
    b->core.l_qname = 10;
    b->core.flag = 0;
    b->core.n_cigar = 1;
    b->core.l_qseq = 100;
    b->core.mtid = -1;
    b->core.mpos = -1;
    b->core.isize = 0;

    // Allocate memory for data
    b->data = (uint8_t *)malloc(size + 10);
    if (b->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }
    memcpy(b->data, data, size);
    b->l_data = size;

    // Initialize kstring_t
    kstring_t str;
    str.l = 0;
    str.m = 0;
    str.s = NULL;

    // Call the function-under-test
    int result = sam_format1(&hdr, b, &str);

    // Clean up
    free(hdr.target_name[0]);
    free(hdr.target_name);
    free(hdr.target_len);
    free(b->data);
    bam_destroy1(b);
    free(str.s);

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

    LLVMFuzzerTestOneInput_159(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
