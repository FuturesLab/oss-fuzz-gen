#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

// Include the necessary C++ compatibility header
#ifdef __cplusplus
extern "C" {
#endif

// Define the function signature for the function under test
GF_EXPORT int gf_isom_update_bitrate_ex(GF_ISOFile *movie, u32 trackNumber, u32 sampleDescriptionIndex, u32 average_bitrate, u32 max_bitrate, u32 decode_buffer_size, Bool forced_for_mpeg4);

#ifdef __cplusplus
}
#endif

int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for extracting multiple u32 values
    if (size < sizeof(u32) * 5 + sizeof(Bool)) {
        return 0;
    }

    // Initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    u32 sampleDescriptionIndex = *((u32 *)(data + sizeof(u32)));
    u32 average_bitrate = *((u32 *)(data + sizeof(u32) * 2));
    u32 max_bitrate = *((u32 *)(data + sizeof(u32) * 3));
    u32 decode_buffer_size = *((u32 *)(data + sizeof(u32) * 4));
    Bool forced_for_mpeg4 = *((Bool *)(data + sizeof(u32) * 5));

    // Call the function under test
    gf_isom_update_bitrate_ex(movie, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size, forced_for_mpeg4);

    // Clean up
    gf_isom_close(movie);

    return 0;
}