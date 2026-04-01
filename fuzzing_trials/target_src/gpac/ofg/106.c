#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 seg_index;

    // Initialize the movie object
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient for extracting trackNumber and seg_index
    if (size < 8) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and seg_index from data
    trackNumber = *((u32 *)data);
    seg_index = *((u32 *)(data + 4));

    // Call the function-under-test
    gf_isom_remove_edit(movie, trackNumber, seg_index);

    // Clean up
    gf_isom_close(movie);

    return 0;
}