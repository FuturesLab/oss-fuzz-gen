#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/kstring.h>

// Function to create a dummy BAM record for testing
bam1_t *create_dummy_bam_record(const uint8_t *data, size_t size) {
    bam1_t *b = bam_init1();
    if (b == NULL) {
        return NULL;
    }
    // Allocate memory for BAM record data
    b->data = (uint8_t *)malloc(size);
    if (b->data == NULL) {
        bam_destroy1(b);
        return NULL;
    }
    memcpy(b->data, data, size);
    b->l_data = size;
    b->core.l_qname = 1; // Minimal valid QNAME length
    b->core.n_cigar = 1; // Minimal valid CIGAR length
    b->core.l_qseq = 1;  // Minimal valid sequence length
    return b;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Check if size is sufficient for testing
    if (size < sizeof(bam1_t)) {
        return 0; // Not enough data to form a valid BAM record
    }

    // Create a dummy BAM record
    bam1_t *b = create_dummy_bam_record(data, size);
    if (b == NULL) {
        return 0; // Failed to create BAM record
    }

    // Initialize the pileup iterator
    bam_plp_t pileup_iterator = bam_plp_init(NULL, NULL);

    // Push the BAM record into the pileup iterator
    bam_plp_push(pileup_iterator, b);

    // Variables for bam_plp_next
    int tid = 0;
    int pos = 0;
    int n_plp = 0;

    // Call the function-under-test
    const bam_pileup1_t *result = bam_plp_next(pileup_iterator, &tid, &pos, &n_plp);

    // Check if result is not NULL to ensure the function is being tested
    if (result != NULL) {
        // Process the result if needed
    }

    // Clean up
    bam_plp_destroy(pileup_iterator);
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

    LLVMFuzzerTestOneInput_22(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
