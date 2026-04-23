#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

// Define a dummy bam1_t object
bam1_t dummy_bam;

// Define a dummy function to simulate the callback required by bam_plp_init
int dummy_callback(void *data, bam1_t *b) {
    if (data == NULL) {
        return -1; // No more reads
    }
    *b = *(bam1_t *)data; // Provide the dummy bam1_t object
    return 1; // Indicate a successful read
}

int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    bam_plp_t pileup;
    int tid = 0;
    hts_pos_t pos = 0;
    int n_plp = 0;

    // Initialize the dummy bam1_t object
    dummy_bam.core.tid = 0;
    dummy_bam.core.pos = 0;
    dummy_bam.core.bin = 0;
    dummy_bam.core.qual = 0;
    dummy_bam.core.l_qname = 1;
    dummy_bam.core.flag = 0;
    dummy_bam.core.n_cigar = 0;
    dummy_bam.core.l_qseq = 0;
    dummy_bam.core.mtid = 0;
    dummy_bam.core.mpos = 0;
    dummy_bam.core.isize = 0;
    dummy_bam.data = (uint8_t *)data;
    dummy_bam.l_data = size;
    dummy_bam.m_data = size;

    // Initialize the pileup object with a dummy callback
    pileup = bam_plp_init(dummy_callback, &dummy_bam);

    if (pileup == NULL) {
        return 0;
    }

    // Call the function-under-test
    const bam_pileup1_t *result = bam_plp64_auto(pileup, &tid, &pos, &n_plp);

    // Cleanup
    bam_plp_destroy(pileup);

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

    LLVMFuzzerTestOneInput_284(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
