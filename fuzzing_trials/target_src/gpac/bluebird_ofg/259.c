#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_259(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(u32) + sizeof(u64)) {
        return 0;
    }

    // Initialize GF_ISOFile structure
    // Provide a temporary directory for the third argument
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp");

    // Extract trackNumber and next_dts from the input data
    u32 trackNumber = *((u32 *)data);
    u64 next_dts = *((u64 *)(data + sizeof(u32)));

    // Call the function under test
    gf_isom_patch_last_sample_duration(movie, trackNumber, next_dts);

    // Clean up
    gf_isom_close(movie);

    return 0;
}