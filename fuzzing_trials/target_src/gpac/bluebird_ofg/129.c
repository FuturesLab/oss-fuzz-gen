#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Initialize trackNumber to a valid value
    GF_ESD esd;
    memset(&esd, 0, sizeof(GF_ESD)); // Initialize esd to zero

    // Create dummy URL and URN names
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";

    u32 outDescriptionIndex = 0; // Initialize output description index

    // Call the function under test
    gf_isom_new_mpeg4_description(movie, trackNumber, &esd, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}