#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htslib/kstring.h"
#include "htslib/sam.h"

extern int bam_plp_insertion(const bam_pileup1_t *, kstring_t *, int *);

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    if (size < sizeof(bam_pileup1_t)) {
        return 0;
    }

    // Initialize bam_pileup1_t
    bam_pileup1_t pileup;
    memset(&pileup, 0, sizeof(bam_pileup1_t));

    // Initialize kstring_t
    kstring_t ks;
    ks.l = 0;
    ks.m = size;
    ks.s = (char *)malloc(size);
    if (ks.s == NULL) {
        return 0;
    }
    memcpy(ks.s, data, size);

    // Initialize an integer
    int n = 0;

    // Call the function under test
    int result = bam_plp_insertion(&pileup, &ks, &n);

    // Clean up
    free(ks.s);

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

    LLVMFuzzerTestOneInput_13(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
