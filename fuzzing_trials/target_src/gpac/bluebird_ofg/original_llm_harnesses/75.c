#include <stdio.h>
#include <stdint.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an interleave time value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize a GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract the interleave time from the input data
    uint32_t InterleaveTime = *((uint32_t *)data);

    // Call the function-under-test
    gf_isom_set_interleave_time(movie, InterleaveTime);

    // Clean up
    gf_isom_close(movie);

    return 0;
}