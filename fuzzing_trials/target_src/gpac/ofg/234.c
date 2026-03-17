#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_234(const uint8_t *data, size_t size) {
    // Ensure there is enough data for all parameters
    if (size < sizeof(uint32_t) * 4 + sizeof(uint8_t) + sizeof(GF_AudioSampleEntryImportMode)) {
        return 0;
    }

    // Initialize parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);

    uint32_t StreamDescriptionIndex = *(uint32_t *)data;
    data += sizeof(uint32_t);

    uint32_t sampleRate = *(uint32_t *)data;
    data += sizeof(uint32_t);

    uint32_t nbChannels = *(uint32_t *)data;
    data += sizeof(uint32_t);

    uint8_t bitsPerSample = *data;
    data += sizeof(uint8_t);

    GF_AudioSampleEntryImportMode asemode = *(GF_AudioSampleEntryImportMode *)data;

    // Call the function under test
    gf_isom_set_audio_info(movie, trackNumber, StreamDescriptionIndex, sampleRate, nbChannels, bitsPerSample, asemode);

    // Clean up
    gf_isom_close(movie);

    return 0;
}