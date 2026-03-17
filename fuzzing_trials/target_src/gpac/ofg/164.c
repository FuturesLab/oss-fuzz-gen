#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Use a valid track number for testing
    const char *schemeURI = "urn:gpac:track:kind:example";
    const char *value = "exampleValue";

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_add_track_kind(movie, trackNumber, schemeURI, value);

    // Close the movie to release resources
    gf_isom_close(movie);

    return 0;
}