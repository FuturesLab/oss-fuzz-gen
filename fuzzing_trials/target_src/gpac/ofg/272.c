#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure we have enough data to extract values
    if (size < 24) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract values from the input data
    u32 trackNumber = *((u32 *)data);
    u32 sampleDescriptionIndex = *((u32 *)(data + 4));
    u32 average_bitrate = *((u32 *)(data + 8));
    u32 max_bitrate = *((u32 *)(data + 12));
    u32 decode_buffer_size = *((u32 *)(data + 16));
    Bool forced_for_mpeg4 = (Bool)(data[20] % 2);

    // Call the function-under-test
    gf_isom_update_bitrate_ex(movie, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size, forced_for_mpeg4);

    // Clean up
    gf_isom_close(movie);

    return 0;
}