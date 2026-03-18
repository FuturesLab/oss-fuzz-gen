#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Assuming at least one track is present
    u32 StreamDescriptionIndex = 1; // Assuming at least one stream description is present
    s32 hSpacing = 1; // Non-zero horizontal spacing
    s32 vSpacing = 1; // Non-zero vertical spacing
    Bool force_par = GF_FALSE; // Boolean value for force_par

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Check if input data is not null and has a valid size
    if (data == NULL || size == 0) {
        gf_isom_close(movie);
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_pixel_aspect_ratio(movie, trackNumber, StreamDescriptionIndex, hSpacing, vSpacing, force_par);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}