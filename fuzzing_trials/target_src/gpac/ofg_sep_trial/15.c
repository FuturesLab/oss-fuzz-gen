#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("/tmp/test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Assuming track number 1 for simplicity
    u8 *sample_data = (u8 *)data;
    u32 data_size = (u32)size;

    // Ensure movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_append_sample_data(movie, trackNumber, sample_data, data_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}