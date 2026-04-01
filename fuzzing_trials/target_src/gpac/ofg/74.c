#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for u32 MajorBrand and u32 MinorVersion
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract MajorBrand and MinorVersion from the input data
    uint32_t MajorBrand = *(const uint32_t *)data;
    uint32_t MinorVersion = *(const uint32_t *)(data + sizeof(uint32_t));

    // Call the function-under-test
    gf_isom_set_brand_info(movie, MajorBrand, MinorVersion);

    // Clean up
    gf_isom_close(movie);

    return 0;
}