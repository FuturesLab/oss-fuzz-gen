#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "htslib/sam.h"

// Dummy function to act as bam_plp_auto_f
int dummy_func(void *data, bam1_t *b) {
    // Simulate processing by initializing bam1_t with some data
    if (b == NULL) {
        return -1; // Return -1 to indicate no more data
    }

    // Populate bam1_t with some dummy data
    b->core.tid = 0; // Dummy reference sequence ID
    b->core.pos = 0; // Dummy position
    b->core.l_qname = 0; // Dummy query name length
    b->core.flag = 0; // Dummy flag
    b->core.n_cigar = 0; // Dummy CIGAR length
    b->core.l_qseq = 0; // Dummy query sequence length
    b->core.mtid = 0; // Dummy mate reference sequence ID
    b->core.mpos = 0; // Dummy mate position
    b->core.isize = 0; // Dummy insert size

    return 1; // Return 1 to indicate data is available
}

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    bam_mplp_t mplp = NULL;

    // Create an array of pointers for data
    void *data_array[1] = { NULL };

    // Initialize bam_mplp_t with the correct number of arguments
    mplp = bam_mplp_init(1, dummy_func, data_array);

    if (mplp == NULL) {
        return 0; // If initialization fails, return early
    }

    // Call the function-under-test with the initialized mplp
    int result = bam_mplp_init_overlaps(mplp);

    // Clean up
    bam_mplp_destroy(mplp);

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

    LLVMFuzzerTestOneInput_26(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
