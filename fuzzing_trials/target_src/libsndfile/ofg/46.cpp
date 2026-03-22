#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sndfile.h>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract the necessary parameters
    if (size < 5) {
        return 0;
    }

    // Open a temporary file to act as a dummy sound file
    const char *temp_filename = "/tmp/temp_soundfile.wav";
    SF_INFO sfinfo;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;

    SNDFILE *sndfile = sf_open(temp_filename, SFM_WRITE, &sfinfo);
    if (sndfile == NULL) {
        return 0;
    }

    // Extract an integer from the data for the 'str_type' parameter
    int str_type = data[0];

    // Use the rest of the data as a string for the 'str' parameter
    const char *str = (const char *)(data + 1);

    // Call the function-under-test
    sf_set_string(sndfile, str_type, str);

    // Close the sound file
    sf_close(sndfile);

    // Remove the temporary file
    remove(temp_filename);

    return 0;
}