#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    if (size < sizeof(bam1_t)) {
        return 0; // Not enough data to form a valid bam1_t structure
    }

    // Allocate memory for bam1_t structure
    bam1_t *bam = (bam1_t *)malloc(sizeof(bam1_t));
    if (bam == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize bam1_t structure
    memset(bam, 0, sizeof(bam1_t)); // Zero out the structure to avoid garbage values

    // Set bam1_t structure fields with some reasonable values
    bam->core.tid = 0; // Example: set to 0, adjust as necessary
    bam->core.pos = 0; // Example: set to 0, adjust as necessary
    bam->core.bin = 0; // Example: set to 0, adjust as necessary
    bam->core.qual = 255; // Example: set to maximum quality
    bam->core.flag = 0; // Example: set to 0, adjust as necessary
    bam->core.n_cigar = 0; // Example: set to 0, adjust as necessary
    bam->core.l_qname = 1; // Example: set to 1, adjust as necessary
    bam->core.l_qseq = 0; // Example: set to 0, adjust as necessary
    bam->core.mtid = -1; // Example: set to -1, adjust as necessary
    bam->core.mpos = -1; // Example: set to -1, adjust as necessary

    // Ensure the data pointer within bam is valid
    bam->l_data = size - sizeof(bam1_t);
    bam->data = (uint8_t *)malloc(bam->l_data);
    if (bam->data == NULL) {
        free(bam);
        return 0; // Memory allocation failed
    }

    // Copy the remaining input data to bam->data
    memcpy(bam->data, data + sizeof(bam1_t), bam->l_data);

    // Call the function-under-test
    bam1_t *dup_bam = bam_dup1(bam);

    // Clean up
    free(bam->data);
    free(bam);
    if (dup_bam != NULL) {
        free(dup_bam->data);
        free(dup_bam);
    }

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

    LLVMFuzzerTestOneInput_251(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
