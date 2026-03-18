#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure the trackNumber is not zero
    u32 trackNumber = 1; // Using a non-zero track number for testing

    // Ensure stsd_data is not NULL
    u8 *stsd_data = (u8 *)malloc(size);
    if (stsd_data == NULL) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy the input data to stsd_data
    memcpy(stsd_data, data, size);

    // Call the function-under-test
    gf_isom_set_track_stsd_templates(movie, trackNumber, stsd_data, size);

    // Clean up
    free(stsd_data);
    gf_isom_close(movie);

    return 0;
}