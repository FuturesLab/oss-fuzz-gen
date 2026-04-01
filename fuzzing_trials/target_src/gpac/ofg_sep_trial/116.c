#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_READ, NULL);
    u32 trackNumber = 1; // Assuming at least one track is present
    u32 movieTime = 0; // Start from the beginning of the movie
    u64 MediaTime = 0;

    // Ensure the_file is not NULL
    if (the_file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_media_time(the_file, trackNumber, movieTime, &MediaTime);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}