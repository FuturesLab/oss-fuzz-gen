#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie;
    u32 trackNumber = 1; // Assuming track number 1 for testing
    u32 data_size = (u32)size;

    // Create a new ISO file for testing
    // Provide a temporary directory path for the third argument
    movie = gf_isom_open(NULL, GF_ISOM_WRITE_EDIT, "/tmp");

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Append sample data
    gf_isom_append_sample_data(movie, trackNumber, (u8 *)data, data_size);

    // Close the ISO file
    gf_isom_close(movie);

    return 0;
}