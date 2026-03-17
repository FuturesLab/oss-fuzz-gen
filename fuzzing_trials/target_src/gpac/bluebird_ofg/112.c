#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming track number 1 for fuzzing
    u8 *sample_data = (u8 *)malloc(size);
    if (!sample_data) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy the input data to sample_data
    for (size_t i = 0; i < size; ++i) {
        sample_data[i] = data[i];
    }

    // Call the function-under-test
    gf_isom_append_sample_data(movie, trackNumber, sample_data, (u32)size);

    // Clean up
    free(sample_data);
    gf_isom_close(movie);

    return 0;
}