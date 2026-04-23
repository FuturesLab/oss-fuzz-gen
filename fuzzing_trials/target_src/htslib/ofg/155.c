#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

// Define a simple iterator function
int iterator_function(void *data, bam1_t *b) {
    const uint8_t *input_data = (const uint8_t *)data;
    size_t size = *((size_t *)((char *)data + sizeof(void *)));

    // Check if we have enough data to simulate a bam1_t record
    if (size >= sizeof(bam1_t)) {
        // Simulate reading a bam1_t structure from input data
        b->data = (uint8_t *)input_data;
        b->l_data = size;
        return 1; // Indicate that a record was read
    }
    return -1; // Indicate end of data
}

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    bam_plp_t plp;
    int tid, n_plp;
    hts_pos_t pos;
    int *n_plp_p = &n_plp;
    int *tid_p = &tid;
    hts_pos_t *pos_p = &pos;

    // Create a context to pass both data and size to the iterator function
    struct {
        const uint8_t *data;
        size_t size;
    } context = { data, size };

    // Initialize bam_plp_t using the iterator function
    plp = bam_plp_init(iterator_function, &context);

    if (plp == NULL) {
        fprintf(stderr, "Failed to initialize bam_plp_t\n");
        return 0;
    }

    // Call the function-under-test
    const bam_pileup1_t *result;
    while ((result = bam_plp64_next(plp, tid_p, pos_p, n_plp_p)) != NULL) {
        // Process the result if needed
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

    LLVMFuzzerTestOneInput_155(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
