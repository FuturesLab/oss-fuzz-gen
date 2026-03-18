#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for our needs
    if (size < sizeof(GF_ISOProfileLevelType) + sizeof(u8)) {
        return 0;
    }

    // Initialize the movie structure
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract GF_ISOProfileLevelType and u8 ProfileLevel from the data
    GF_ISOProfileLevelType PL_Code = *(GF_ISOProfileLevelType *)data;
    u8 ProfileLevel = *(u8 *)(data + sizeof(GF_ISOProfileLevelType));

    // Call the function-under-test
    gf_isom_set_pl_indication(movie, PL_Code, ProfileLevel);

    // Clean up
    gf_isom_close(movie);

    return 0;
}