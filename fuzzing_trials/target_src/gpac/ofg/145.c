#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming there's at least one track
    const char *xmlnamespace = "http://www.example.com/namespace";
    const char *xml_schema_loc = "http://www.example.com/schema";
    const char *mimes = "application/xml";
    u32 outDescriptionIndex = 0;

    // Ensure data is large enough to be used as a string
    char *data_as_string = NULL;
    if (size > 0) {
        data_as_string = (char *)malloc(size + 1);
        if (data_as_string) {
            memcpy(data_as_string, data, size);
            data_as_string[size] = '\0'; // Null-terminate the string
        }
    }

    gf_isom_new_xml_subtitle_description(movie, trackNumber, xmlnamespace, xml_schema_loc, mimes, &outDescriptionIndex);

    if (data_as_string) {
        free(data_as_string);
    }

    gf_isom_close(movie);

    return 0;
}