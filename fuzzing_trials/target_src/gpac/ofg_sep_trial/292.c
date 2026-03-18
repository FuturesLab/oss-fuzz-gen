#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;  // Arbitrary non-zero track number
    const char *URLname = "http://example.com";  // Example URL
    const char *URNname = "urn:example";  // Example URN
    u32 outDescriptionIndex = 0;
    const char *config = "example_config";  // Example configuration

    // Ensure the data is not null and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_new_webvtt_description(movie, trackNumber, URLname, URNname, &outDescriptionIndex, config);

    // Clean up
    if (movie != NULL) {
        gf_isom_close(movie);
    }

    return 0;
}