#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_282(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 MajorBrand, MinorVersion;

    // Ensure the size is sufficient to extract MajorBrand and MinorVersion
    if (size < 8) {
        return 0;
    }

    // Initialize MajorBrand and MinorVersion from the input data
    MajorBrand = *((u32 *)data);
    MinorVersion = *((u32 *)(data + 4));

    // Create a new ISO file structure
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_brand_info(movie, MajorBrand, MinorVersion);

    // Close the ISO file and free resources
    gf_isom_close(movie);

    return 0;
}