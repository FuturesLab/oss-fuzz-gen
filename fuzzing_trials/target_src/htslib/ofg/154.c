#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include for memcpy
#include <htslib/sam.h>
#include <htslib/hts.h>

// Static function to simulate filling the bam1_t structure with data
static int dummy_iter_func(void *data, bam1_t *b) {
    const uint8_t *input_data = (const uint8_t *)data;
    size_t size = *((size_t *)input_data); // Assuming the size is passed as the first element

    if (size < sizeof(bam1_t)) {
        return -1; // Not enough data to fill a bam1_t structure
    }

    // Ensure the bam1_t structure is properly initialized
    b->data = (uint8_t *)malloc(size);
    if (b->data == NULL) {
        return -1; // Memory allocation failure
    }

    // Simulate filling the bam1_t structure with data
    memcpy(b->data, input_data + sizeof(size_t), size - sizeof(size_t));
    b->l_data = size - sizeof(size_t); // Set the length of the data

    // Set other fields in bam1_t to simulate a more realistic scenario
    b->core.tid = 0; // Example: set the reference sequence ID
    b->core.pos = 0; // Example: set the position

    return 0; // Indicate that data was provided
}

// Function prototype for the fuzzer entry point
int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    bam_plp_t plp;
    int tid = 0;
    hts_pos_t pos = 0;
    int n_plp = 0;

    // Initialize the pileup object using the dummy iterator function
    plp = bam_plp_init(dummy_iter_func, (void *)data);

    if (plp == NULL) {
        return 0;
    }

    // Call the function-under-test
    const bam_pileup1_t *result = bam_plp64_next(plp, &tid, &pos, &n_plp);

    // Check if result is non-null to ensure the function is being exercised
    if (result != NULL) {
        // Optionally, perform additional checks or processing on `result`
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_154(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
