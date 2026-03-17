#include <stdint.h>
#include <stddef.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract all required parameters
    if (size < sizeof(u32) * 4 + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode)) {
        return 0;
    }

    // Initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    u32 StreamDescriptionIndex = *((u32 *)(data + sizeof(u32)));
    u32 sampleRate = *((u32 *)(data + 2 * sizeof(u32)));
    u32 nbChannels = *((u32 *)(data + 3 * sizeof(u32)));
    u8 bitsPerSample = *(data + 4 * sizeof(u32));
    GF_AudioSampleEntryImportMode asemode = *(GF_AudioSampleEntryImportMode *)(data + 4 * sizeof(u32) + sizeof(u8));

    // Call the function-under-test
    gf_isom_set_audio_info(movie, trackNumber, StreamDescriptionIndex, sampleRate, nbChannels, bitsPerSample, asemode);

    // Clean up
    gf_isom_close(movie);

    return 0;
}