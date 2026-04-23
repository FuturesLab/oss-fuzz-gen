#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>

// Mock function to create a bam_plp_t object for demonstration purposes
bam_plp_t create_bam_plp() {
    // Create a dummy bam1_t object
    bam1_t *b = bam_init1();
    if (!b) {
        fprintf(stderr, "Failed to initialize bam1_t\n");
        exit(1);
    }

    // Initialize bam_plp_t with a dummy iterator function and the bam1_t object
    bam_plp_t plp = bam_plp_init((bam_plp_auto_f)bam_read1, b);
    if (!plp) {
        fprintf(stderr, "Failed to initialize bam_plp_t\n");
        bam_destroy1(b);
        exit(1);
    }

    return plp;
}

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize variables for bam_plp_next parameters
    bam_plp_t plp = create_bam_plp();
    int tid = 0;
    int pos = 0;
    int n_plp = 0;

    // Simulate feeding data into the bam_plp_t object
    // For demonstration, we assume data is a valid BAM record
    bam1_t *b = bam_init1();
    if (!b) {
        fprintf(stderr, "Failed to initialize bam1_t\n");
        bam_plp_destroy(plp);
        return 0;
    }

    // Copy data into bam1_t structure
    if (size >= sizeof(bam1_core_t)) {
        memcpy(&b->core, data, sizeof(bam1_core_t));
        b->l_data = size - sizeof(bam1_core_t);
        b->data = (uint8_t *)malloc(b->l_data);
        if (b->data) {
            memcpy(b->data, data + sizeof(bam1_core_t), b->l_data);
        }
    }

    // Call the function-under-test
    const bam_pileup1_t *result = bam_plp_next(plp, &tid, &pos, &n_plp);

    // Clean up resources
    bam_destroy1(b);
    bam_plp_destroy(plp);

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

    LLVMFuzzerTestOneInput_21(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
