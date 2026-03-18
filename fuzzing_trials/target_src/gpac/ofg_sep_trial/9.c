#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    u32 trackNumber = 1; // Assuming track number 1 for testing
    GF_TextSampleDescriptor desc;
    memset(&desc, 0, sizeof(GF_TextSampleDescriptor)); // Initialize descriptor

    // Create dummy URLname and URNname
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_new_text_description(movie, trackNumber, &desc, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}