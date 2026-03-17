#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the required parameters
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize the parameters for gf_isom_set_brand_info
    // Provide a valid temporary directory path for the third parameter
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp");
    if (movie == NULL) {
        return 0;
    }

    // Extract MajorBrand and MinorVersion from the input data
    uint32_t MajorBrand = *((uint32_t *)data);
    uint32_t MinorVersion = *((uint32_t *)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_set_brand_info(movie, MajorBrand, MinorVersion);

    // Clean up
    gf_isom_close(movie);

    return 0;
}