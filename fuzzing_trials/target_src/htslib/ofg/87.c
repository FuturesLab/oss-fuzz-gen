#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <htslib/hts.h>

// Function prototype for the fuzzing entry point
int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize htsFormat
    if (size < sizeof(htsFormat)) {
        return 0;
    }

    // Allocate memory for htsFormat
    htsFormat *format = (htsFormat *)malloc(sizeof(htsFormat));
    if (!format) {
        return 0;
    }

    // Copy data into htsFormat structure
    memcpy(format, data, sizeof(htsFormat));

    // Call the function-under-test
    char *description = hts_format_description(format);

    // If a description was returned, free it
    if (description) {
        free(description);
    }

    // Free the allocated htsFormat
    free(format);

    return 0;
}