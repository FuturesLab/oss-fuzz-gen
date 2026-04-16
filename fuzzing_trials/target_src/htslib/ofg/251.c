#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    int cache_size;

    // Ensure size is sufficient to extract an integer for cache_size
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize cache_size from the input data
    cache_size = *((int *)data);

    // Open a dummy htsFile to pass to the function
    file = hts_open("dummy.bam", "wb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    hts_set_cache_size(file, cache_size);

    // Clean up
    hts_close(file);

    return 0;
}