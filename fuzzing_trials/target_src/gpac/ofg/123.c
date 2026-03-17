#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Include the necessary headers for GF_ISOFile and gf_isom_remove_track_kind
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary parameters
    if (size < sizeof(uint32_t) + 2) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *movie = gf_isom_open_file("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Use the remaining data to create strings for schemeURI and value
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
    gf_isom_remove_track_kind(movie, trackNumber, schemeURI, value);

    // Clean up
    gf_isom_close(movie);

    return 0;
}