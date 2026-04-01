#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>  // Assuming this header defines GF_ISOFile and related functions/types

int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Ensure there's enough data to use for the parameters
    if (size < sizeof(uint32_t) * 3 + 2) {
        return 0;
    }

    // Initialize the parameters
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);  // Use gf_isom_open to create a new GF_ISOFile
    if (!movie) return 0;  // Check for successful creation

    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    const char *URLname = (const char *)data;
    size_t urlLength = strnlen(URLname, size);
    data += urlLength + 1;  // Move past the URL string and null terminator
    size -= urlLength + 1;

    const char *URNname = (const char *)data;
    size_t urnLength = strnlen(URNname, size);
    data += urnLength + 1;  // Move past the URN string and null terminator
    size -= urnLength + 1;

    uint32_t *outDescriptionIndex = (uint32_t *)malloc(sizeof(uint32_t));  // Allocate memory for outDescriptionIndex
    if (!outDescriptionIndex) {
        gf_isom_close(movie);
        return 0;  // Check for successful allocation
    }

    uint8_t *dsi = (uint8_t *)data;
    uint32_t dsi_size = size >= sizeof(uint32_t) ? *((uint32_t *)data) : 0;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    uint32_t mha_subtype = size >= sizeof(uint32_t) ? *((uint32_t *)data) : 0;

    // Call the function-under-test
    gf_isom_new_mpha_description(movie, trackNumber, URLname, URNname, outDescriptionIndex, dsi, dsi_size, mha_subtype);

    // Clean up
    gf_isom_close(movie);
    free(outDescriptionIndex);

    return 0;
}