#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u32 trackNumber;
    u32 sampleDescIndex;
    const u32 *profiles;
    u32 nb_compat_profiles;
    
    // Initialize variables
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient to extract necessary values
    if (size < sizeof(u32) * 3) {
        gf_isom_close(movie);
        return 0;
    }

    trackNumber = *((u32 *)data);
    sampleDescIndex = *((u32 *)(data + sizeof(u32)));
    nb_compat_profiles = *((u32 *)(data + 2 * sizeof(u32)));

    // Ensure there is enough data for profiles
    if (size < 3 * sizeof(u32) + nb_compat_profiles * sizeof(u32)) {
        gf_isom_close(movie);
        return 0;
    }

    profiles = (const u32 *)(data + 3 * sizeof(u32));

    // Call the function-under-test
    gf_isom_set_mpegh_compatible_profiles(movie, trackNumber, sampleDescIndex, profiles, nb_compat_profiles);

    // Clean up
    gf_isom_close(movie);

    return 0;
}