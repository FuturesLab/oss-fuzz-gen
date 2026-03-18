#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for extracting parameters
    if (size < 12) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = (u32)data[0]; // Use first byte for trackNumber
    u32 type = (u32)data[1]; // Use second byte for type

    // Create dummy strings for mime, encoding, and config
    const char *mime = "video/mp4";
    const char *encoding = "utf-8";
    const char *config = "config";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_new_stxt_description(movie, trackNumber, type, mime, encoding, config, &outDescriptionIndex);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}