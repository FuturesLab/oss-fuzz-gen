#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0; // Exit if movie creation fails
    }

    u32 trackNumber = 1; // Use a valid track number
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    GF_GenericSampleDescription udesc;
    u32 outDescriptionIndex = 0;

    // Initialize udesc with some default values
    memset(&udesc, 0, sizeof(GF_GenericSampleDescription));

    // Call the function-under-test
    gf_isom_new_generic_sample_description(movie, trackNumber, URLname, URNname, &udesc, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}