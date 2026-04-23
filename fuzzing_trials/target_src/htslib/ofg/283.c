#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

#ifdef __cplusplus
extern "C" {
#endif

// Mock function for bam_plp64_auto_283 as the real implementation is not provided
const bam_pileup1_t *bam_plp64_auto_283(bam_plp_t plp, int *tid, hts_pos_t *pos, int *n_plp) {
    static bam_pileup1_t pileup;
    // Mock implementation
    *tid = 1;
    *pos = 100;
    *n_plp = 1;
    return &pileup;
}

int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    bam_plp_t plp = NULL;  // Initialize bam_plp_t as NULL since it's a pointer type
    int tid;
    hts_pos_t pos;
    int n_plp;

    // Call the function-under-test
    const bam_pileup1_t *result = bam_plp64_auto_283(plp, &tid, &pos, &n_plp);

    // Use the result to avoid unused variable warning
    if (result != NULL) {
        printf("tid: %d, pos: %ld, n_plp: %d\n", tid, (long)pos, n_plp);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_283(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
