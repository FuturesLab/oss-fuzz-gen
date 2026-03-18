#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    u32 trackNumber = 1; // Example track number
    u32 type = 0; // Example type, adjust as needed

    // Ensure non-NULL strings for mime, encoding, and config
    const char *mime = "application/ttml+xml";
    const char *encoding = "UTF-8";
    const char *config = "example-config";

    u32 outDescriptionIndex;

    // Call the function-under-test
    gf_isom_new_stxt_description(movie, trackNumber, type, mime, encoding, config, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}