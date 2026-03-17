#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 sampleDescIndex;
    u32 *profiles;  // Changed from const u32 * to u32 *
    u32 nb_compat_profiles;

    // Initialize variables
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    trackNumber = (size > 0) ? data[0] : 1;
    sampleDescIndex = (size > 1) ? data[1] : 1;
    nb_compat_profiles = (size > 2) ? data[2] : 1;

    // Allocate memory for profiles
    profiles = (u32 *)malloc(nb_compat_profiles * sizeof(u32));
    if (!profiles) {
        gf_isom_close(movie);
        return 0;
    }

    // Fill profiles with data
    for (u32 i = 0; i < nb_compat_profiles; i++) {
        profiles[i] = (size > (3 + i)) ? data[3 + i] : 0;
    }

    // Call the function-under-test
    gf_isom_set_mpegh_compatible_profiles(movie, trackNumber, sampleDescIndex, profiles, nb_compat_profiles);

    // Clean up
    free(profiles);
    gf_isom_close(movie);

    return 0;
}