#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 StreamDescriptionIndex;

    // Allocate memory for the movie structure
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);

    // Ensure movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Initialize trackNumber and StreamDescriptionIndex with non-zero values
    trackNumber = 1;
    StreamDescriptionIndex = 1;

    // Call the function-under-test
    gf_isom_remove_stream_description(movie, trackNumber, StreamDescriptionIndex);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}