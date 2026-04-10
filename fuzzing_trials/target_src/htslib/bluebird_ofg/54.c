#include <stdint.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int threads = *((int *)data);

    // Limit the number of threads to a reasonable number to prevent excessive resource usage
    if (threads < 1 || threads > 16) {
        return 0;
    }

    // Use a safer approach by opening a temporary file in memory
    htsFile *file = hts_open("-", "wb"); // "-" indicates standard output, which is safe for fuzzing
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    hts_set_threads(file, threads);

    // Close the htsFile
    hts_close(file);

    return 0;
}