#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Ensure there's enough data for trackNumber
    }

    // Initialize a GF_ISOFile object
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);

    // Extract trackNumber from the input data
    u32 trackNumber = *((u32 *)data);

    // Create non-NULL schemeURI and value strings
    const char *schemeURI = "http://example.com/scheme";
    const char *value = "example_value";

    // Call the function-under-test
    gf_isom_remove_track_kind(movie, trackNumber, schemeURI, value);

    // Clean up
    if (movie != NULL) {
        gf_isom_close(movie);
    }

    return 0;
}