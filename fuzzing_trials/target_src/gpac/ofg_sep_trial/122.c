#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the data size is sufficient for trackNumber and strings
    if (size < sizeof(uint32_t) + 2) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Extract schemeURI and value strings from the remaining data
    size_t schemeURILen = strnlen((const char *)data, size);
    const char *schemeURI = (const char *)data;
    data += schemeURILen + 1;
    size -= schemeURILen + 1;

    size_t valueLen = strnlen((const char *)data, size);
    const char *value = (const char *)data;

    // Call the function under test
    gf_isom_remove_track_kind(movie, trackNumber, schemeURI, value);

    // Clean up
    gf_isom_close(movie);

    return 0;
}