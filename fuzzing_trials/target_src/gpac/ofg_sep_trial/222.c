#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract required parameters
    if (size < sizeof(u32) * 2 + sizeof(GF_AudioChannelLayout)) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Extract trackNumber and sampleDescriptionIndex from data
    u32 trackNumber = *((u32 *)data);
    u32 sampleDescriptionIndex = *((u32 *)(data + sizeof(u32)));

    // Extract GF_AudioChannelLayout from data
    GF_AudioChannelLayout layout;
    memcpy(&layout, data + sizeof(u32) * 2, sizeof(GF_AudioChannelLayout));

    // Call the function-under-test
    gf_isom_set_audio_layout(movie, trackNumber, sampleDescriptionIndex, &layout);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}