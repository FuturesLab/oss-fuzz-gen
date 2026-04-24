#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>  // Include the necessary header for bam_mplp_t

// Define a dummy function to pass to bam_mplp_init
int dummy_func_16(void *data, bam1_t *b) {
    // Simulate reading a BAM record
    // For fuzzing, we can try to interpret the input data as a bam1_t structure
    if (data == NULL || b == NULL) {
        return -1; // Return -1 to indicate no more data
    }

    // Cast the input data to bam1_t and simulate a read
    bam1_t *input_bam = (bam1_t *)data;
    *b = *input_bam; // Copy the input data to the bam1_t structure

    return 0; // Return 0 to indicate successful read
}

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    if (size < sizeof(bam1_t)) {
        return 0; // Exit if the input size is too small
    }

    // Create an array of pointers for the data argument
    bam1_t input_bam;
    memcpy(&input_bam, data, sizeof(bam1_t)); // Copy input data to bam1_t structure
    void *data_array[1] = { &input_bam };

    // Declare and initialize the bam_mplp_t variable
    bam_mplp_t mplp = bam_mplp_init(1, dummy_func_16, data_array);

    // Check if the initialization was successful
    if (mplp == NULL) {
        return 0; // Exit if initialization failed
    }

    // Simulate data processing by calling bam_mplp_auto
    int tid, pos, n_plp;
    const bam_pileup1_t **plp;

    // We need to simulate a loop that processes data
    while (bam_mplp_auto(mplp, &tid, &pos, &n_plp, &plp) > 0) {
        // Process the pileup data
        for (int i = 0; i < n_plp; ++i) {
            // Example: just access the data to simulate processing
            const bam_pileup1_t *p = plp[i];
            if (p->is_del) {
                // Handle deletion
            }
            if (p->is_refskip) {
                // Handle reference skip
            }
        }
    }

    // Call the function-under-test
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_16(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
