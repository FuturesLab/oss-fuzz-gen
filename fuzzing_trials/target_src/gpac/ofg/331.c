#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract necessary parameters
    if (size < 16) {
        return 0;
    }

    // Initialize parameters for gf_isom_new_mpha_description
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = (u32)data[0];
    const char *URLname = (const char *)(data + 1);
    const char *URNname = (const char *)(data + 5);
    u32 outDescriptionIndex = 0;
    u8 *dsi = (u8 *)(data + 9);
    u32 dsi_size = (u32)(size - 9);
    u32 mha_subtype = (u32)data[8];

    // Call the function-under-test
    gf_isom_new_mpha_description(movie, trackNumber, URLname, URNname, &outDescriptionIndex, dsi, dsi_size, mha_subtype);

    // Clean up
    gf_isom_close(movie);

    return 0;
}