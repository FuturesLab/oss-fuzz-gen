#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read the required parameters
    if (size < 3 * sizeof(u32) + 2 * sizeof(s32) + sizeof(Bool)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open((const char *)data, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Read parameters from the input data
    u32 trackNumber = *(u32 *)(data);
    u32 StreamDescriptionIndex = *(u32 *)(data + sizeof(u32));
    s32 hSpacing = *(s32 *)(data + 2 * sizeof(u32));
    s32 vSpacing = *(s32 *)(data + 2 * sizeof(u32) + sizeof(s32));
    Bool force_par = *(Bool *)(data + 2 * sizeof(u32) + 2 * sizeof(s32));

    // Call the function-under-test
    gf_isom_set_pixel_aspect_ratio(movie, trackNumber, StreamDescriptionIndex, hSpacing, vSpacing, force_par);

    // Clean up
    gf_isom_close(movie);

    return 0;
}