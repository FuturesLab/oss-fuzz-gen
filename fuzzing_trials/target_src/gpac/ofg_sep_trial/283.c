#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for extracting MajorBrand and MinorVersion
    if (size < 8) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract MajorBrand and MinorVersion from the input data
    u32 MajorBrand = *((u32*)data);
    u32 MinorVersion = *((u32*)(data + 4));

    // Call the function-under-test
    gf_isom_set_brand_info(movie, MajorBrand, MinorVersion);

    // Clean up
    gf_isom_close(movie);

    return 0;
}