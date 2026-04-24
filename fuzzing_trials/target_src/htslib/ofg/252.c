#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    if (size < 32) {
        // Ensure there is enough data to fill the BAM structure meaningfully
        return 0;
    }

    bam1_t *bam = bam_init1();
    if (bam == NULL) {
        return 0;
    }

    // Allocate space for the BAM data
    bam->data = (uint8_t *)malloc(size);
    if (bam->data == NULL) {
        bam_destroy1(bam);
        return 0;
    }
    memcpy(bam->data, data, size);
    bam->l_data = size;

    // Initialize core fields with some valid values
    bam->core.tid = data[0] % 25;  // Reference sequence ID
    bam->core.pos = data[1] | (data[2] << 8);  // 0-based leftmost coordinate
    bam->core.bin = data[3];  // Bin for indexing
    bam->core.qual = data[4];  // Mapping quality
    bam->core.l_qname = data[5] % 256;  // Length of the query name
    bam->core.flag = data[6];  // Bitwise flag
    bam->core.n_cigar = data[7] % 5;  // Number of CIGAR operations
    bam->core.l_qseq = data[8] % 100;  // Length of the query sequence
    bam->core.mtid = data[9] % 25;  // Mate reference sequence ID
    bam->core.mpos = data[10] | (data[11] << 8);  // 0-based leftmost mate coordinate
    bam->core.isize = data[12] | (data[13] << 8);  // Insert size

    // Ensure the query name is set
    if (bam->core.l_qname > 0 && size >= bam->core.l_qname) {
        memcpy(bam->data, data + 14, bam->core.l_qname);
    }

    // Call the function-under-test
    bam1_t *dup_bam = bam_dup1(bam);

    // Clean up
    if (dup_bam != NULL) {
        bam_destroy1(dup_bam);
    }
    bam_destroy1(bam);

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

    LLVMFuzzerTestOneInput_252(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
