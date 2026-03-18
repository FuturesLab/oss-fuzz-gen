#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    if (size < 2) {
        gf_isom_close(movie);
        return 0;
    }

    GF_ISOProfileLevelType PL_Code = (GF_ISOProfileLevelType)data[0];
    u8 ProfileLevel = data[1];

    gf_isom_set_pl_indication(movie, PL_Code, ProfileLevel);

    gf_isom_close(movie);
    return 0;
}