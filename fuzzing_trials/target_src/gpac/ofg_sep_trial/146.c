#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Assume a valid track number
    const char *xmlnamespace = "urn:example:namespace";
    const char *xml_schema_loc = "http://example.com/schema.xsd";
    const char *mimes = "application/xml";
    u32 outDescriptionIndex = 0;

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Call the function under test
    gf_isom_new_xml_subtitle_description(movie, trackNumber, xmlnamespace, xml_schema_loc, mimes, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}