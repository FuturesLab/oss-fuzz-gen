#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>

// Mock function to create a non-NULL hts_idx_t pointer for testing
hts_idx_t* create_test_hts_idx() {
    // In a real scenario, you would create or load an actual index
    // Here, we simply return a dummy pointer for testing
    return (hts_idx_t*)0x1; // Return a non-NULL dummy pointer
}

int LLVMFuzzerTestOneInput_235(const uint8_t *data, size_t size) {
    hts_idx_t *idx = create_test_hts_idx();
    int tid = 0; // Example value, as the actual value depends on the index
    uint64_t mapped = 0;
    uint64_t unmapped = 0;

    if (idx == NULL) {
        return 0; // Exit if index creation failed
    }

    // Call the function-under-test
    int result = hts_idx_get_stat(idx, tid, &mapped, &unmapped);

    // Output the result and stats for debugging purposes
    printf("Result: %d, Mapped: %" PRIu64 ", Unmapped: %" PRIu64 "\n", result, mapped, unmapped);

    // Free the allocated index
    // Note: Since we used a dummy pointer, we should not actually free it.
    // free(idx);

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

    LLVMFuzzerTestOneInput_235(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
