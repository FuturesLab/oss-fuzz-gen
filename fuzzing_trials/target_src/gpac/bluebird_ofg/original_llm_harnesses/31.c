#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure trackNumber is within a reasonable range
    u32 trackNumber = (size > 0) ? data[0] % 10 + 1 : 1; // Example track number

    // Ensure schemeURI and value are non-null and null-terminated
    const char *schemeURI = "urn:example:scheme";
    const char *value = "example_value";

    // Call the function-under-test
    gf_isom_remove_track_kind(movie, trackNumber, schemeURI, value);

    // Close the movie to free resources
    gf_isom_close(movie);

    return 0;
}