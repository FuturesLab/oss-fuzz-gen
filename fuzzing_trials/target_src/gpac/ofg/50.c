#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h> // Assuming this is the correct header file for GF_ISOFile and related functions

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(data, size, GF_ISOM_OPEN_READ); // Attempt to open an ISO file from memory
    u32 trackNumber = 1; // Set a non-zero track number
    u32 StreamDescriptionIndex = 1; // Set a non-zero stream description index

    // Ensure the movie object was created successfully
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_remove_stream_description(movie, trackNumber, StreamDescriptionIndex);

    // Clean up and close the movie object
    gf_isom_close(movie);

    return 0;
}