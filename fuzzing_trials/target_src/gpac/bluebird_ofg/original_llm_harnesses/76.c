#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Include additional necessary headers for constants like u32, u64

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough for the required fields
    if (size < sizeof(u32) * 2 + sizeof(u64)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber, StreamDescriptionIndex, and dataOffset from the input data
    u32 trackNumber = *((u32 *)data);
    u32 StreamDescriptionIndex = *((u32 *)(data + sizeof(u32)));
    u64 dataOffset = *((u64 *)(data + sizeof(u32) * 2));

    // Initialize the GF_ISOSample structure
    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Call the function-under-test
    gf_isom_add_sample_reference(movie, trackNumber, StreamDescriptionIndex, sample, dataOffset);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}