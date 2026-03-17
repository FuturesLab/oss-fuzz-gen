#include <stdint.h>
#include <stddef.h>
#include "/src/gpac/include/gpac/isomedia.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1;  // Initialize trackNumber to a non-zero value

    // Check if the input data is not null and has a reasonable size
    if (data == NULL || size == 0) {
        return 0;  // Exit if the input data is null or size is zero
    }

    // Assume the movie is initialized elsewhere or use a mock for fuzzing
    // movie = gf_isom_new();  // Removed as per instructions

    // Call the function-under-test
    gf_isom_add_track_to_root_od(movie, trackNumber);

    // Close the ISO file
    gf_isom_close(movie);

    return 0;
}

#ifdef __cplusplus
}
#endif