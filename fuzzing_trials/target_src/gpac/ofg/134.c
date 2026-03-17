#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include this for u32 and Bool definitions
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Assume a reasonable minimum size for fuzzing purposes
    const size_t min_size = 12; // Adjusted to a fixed value for fuzzing

    // Ensure the size is sufficient for initializing parameters
    if (size < min_size) {
        return 0;
    }

    // Open an empty ISO file structure for fuzzing
    // Provide a temporary directory path as the third argument
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, "/tmp");
    if (!movie) {
        return 0;
    }

    // Extract parameters from input data
    u32 media_segment_type = *((u32 *)(data + 4)); // Assuming 4 bytes offset for u32
    Bool mvex_after_tracks = *((Bool *)(data + 8)); // Assuming 8 bytes offset for Bool

    // Call the function-under-test
    gf_isom_finalize_for_fragment(movie, media_segment_type, mvex_after_tracks);

    // Clean up
    gf_isom_close(movie);

    return 0;
}