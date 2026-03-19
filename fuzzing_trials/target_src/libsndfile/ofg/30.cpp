#include <stdint.h>
#include <stddef.h>
#include <sndfile.h>

extern "C" {
    // Function signature from the provided task
    int sf_format_check(const SF_INFO *);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to fill SF_INFO
    if (size < sizeof(SF_INFO)) {
        return 0;
    }

    // Initialize SF_INFO structure with non-null values
    SF_INFO sfinfo;
    sfinfo.frames = 1; // Non-zero value
    sfinfo.samplerate = 44100; // Common sample rate
    sfinfo.channels = 2; // Stereo
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Common format
    sfinfo.sections = 1; // Non-zero value
    sfinfo.seekable = 1; // Non-zero value

    // Call the function-under-test
    sf_format_check(&sfinfo);

    return 0;
}