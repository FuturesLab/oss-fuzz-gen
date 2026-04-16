#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <htslib/hts.h>
#include <htslib/sam.h>
#include <htslib/bgzf.h>

// Define a helper function to create a valid htsFormat
htsFormat create_valid_htsFormat() {
    htsFormat format;
    format.category = unknown_category; // Use a valid category
    format.format = unknown_format;     // Use a valid format
    return format;
}

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize htsFile structure in memory
    htsFile *file = hts_open("-", "wb"); // Use "-" to write to stdout (memory-based)
    if (file == NULL) {
        return 0;
    }

    // Use a valid htsFormat
    htsFormat format = create_valid_htsFormat();

    // Extract an integer value from the data for the void* parameter
    int value = *(int *)data;

    // Call the function-under-test
    int result = hts_set_opt(file, format.category, (void *)&value);

    // Check the result if necessary (for debugging purposes)
    if (result != 0) {
        fprintf(stderr, "hts_set_opt failed with result: %d\n", result);
    }

    // Clean up
    hts_close(file);

    return 0;
}