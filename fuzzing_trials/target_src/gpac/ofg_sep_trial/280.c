#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract meaningful values
    if (size < sizeof(u32) + sizeof(Bool)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from the input data
    u32 trackNumber = *(u32 *)data;

    // Extract remove flag from the input data
    Bool remove = *(Bool *)(data + sizeof(u32));

    // Call the function-under-test
    gf_isom_update_aperture_info(movie, trackNumber, remove);

    // Clean up
    gf_isom_close(movie);

    return 0;
}