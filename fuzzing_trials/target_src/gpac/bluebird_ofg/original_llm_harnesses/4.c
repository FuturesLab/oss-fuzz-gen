#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <string.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract necessary parameters
    if (size < 8) {
        return 0;
    }

    // Initialize movie
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from the input data
    u32 trackNumber = *((u32 *)data);
    data += 4;
    size -= 4;

    // Extract schemeURI and value from the input data
    const char *schemeURI = (const char *)data;
    size_t schemeURILen = strnlen(schemeURI, size);
    if (schemeURILen == size) {
        gf_isom_close(movie);
        return 0;
    }
    data += schemeURILen + 1;
    size -= schemeURILen + 1;

    const char *value = (const char *)data;
    size_t valueLen = strnlen(value, size);
    if (valueLen == size) {
        gf_isom_close(movie);
        return 0;
    }

    // Call the function-under-test
    gf_isom_add_track_kind(movie, trackNumber, schemeURI, value);

    // Clean up
    gf_isom_close(movie);

    return 0;
}