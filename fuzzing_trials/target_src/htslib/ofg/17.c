#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

// Define a dummy function to pass as the bam_plp_auto_f function
int dummy_func_17(bam_plp_t iter, void *data, int *tid, int *pos, int *n_plp, const bam_pileup1_t **plp) {
    // Provide a simple implementation that simulates pileup data
    static int call_count = 0;
    if (call_count++ > 10) {
        return 0; // Return 0 to indicate no more data after 10 calls
    }
    *tid = 0;
    *pos = call_count;
    *n_plp = 1;
    static bam_pileup1_t pileup;
    *plp = &pileup;
    return 1; // Return 1 to indicate more data is available
}

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    if (size < sizeof(bam1_t)) {
        return 0; // Not enough data to form a valid bam1_t structure
    }

    bam_mplp_t mplp;
    int n = 1; // number of samples

    // Create a dummy data array with a non-NULL bam1_t structure
    bam1_t *b = bam_init1();
    if (!b) {
        return 0; // Memory allocation failed
    }

    // Ensure the bam1_t structure has enough space
    if (b->m_data < size) {
        b->m_data = size;
        b->data = realloc(b->data, b->m_data);
        if (!b->data) {
            bam_destroy1(b);
            return 0; // Memory allocation failed
        }
    }

    // Copy input data into the bam1_t structure
    memcpy(b->data, data, size);

    void *dummy_data[1] = { b };

    // Initialize mplp with the correct number of arguments
    mplp = bam_mplp_init(n, dummy_func_17, dummy_data);

    // Call the function-under-test
    int tid, pos, n_plp;
    const bam_pileup1_t *plp;
    while (bam_mplp_auto(mplp, &tid, &pos, &n_plp, &plp)) {
        // Process the pileup data
    }

    // Clean up
    bam_mplp_destroy(mplp);
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

    LLVMFuzzerTestOneInput_17(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
