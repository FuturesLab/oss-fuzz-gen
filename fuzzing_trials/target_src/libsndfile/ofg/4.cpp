#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for close function

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Create a temporary file to use with SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;
    }

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the file with SFM_WRITE mode
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (!sndfile) {
        close(fd);
        return 0;
    }

    // Ensure size is a multiple of sizeof(float) for proper casting
    size_t float_count = size / sizeof(float);
    if (float_count > 0) {
        const float *float_data = reinterpret_cast<const float *>(data);

        // Call the function-under-test
        sf_write_float(sndfile, float_data, static_cast<sf_count_t>(float_count));
    }

    // Clean up
    sf_close(sndfile);
    close(fd);
    remove(tmpl);

    return 0;
}