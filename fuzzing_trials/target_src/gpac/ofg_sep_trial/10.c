#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "gpac/isomedia.h" // Assuming this is the correct header file for the function

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL); // Create a temporary movie file
    if (!movie) return 0;

    u32 trackNumber = 1; // Example track number
    GF_TextSampleDescriptor desc; // Initialize a text sample descriptor
    memset(&desc, 0, sizeof(GF_TextSampleDescriptor)); // Clear the descriptor

    // Create non-NULL URLname and URNname
    char URLname[256] = "http://example.com";
    char URNname[256] = "urn:example";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_new_text_description(movie, trackNumber, &desc, URLname, URNname, &outDescriptionIndex);

    // Cleanup
    gf_isom_close(movie);

    return 0;
}