#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Define and initialize variables
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    float *buffer;
    sf_count_t frames;

    // Ensure the data size is sufficient to avoid segmentation faults
    if (size < sizeof(float)) {
        return 0;
    }

    // Create a temporary file to be used by libsndfile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;
    }

    // Initialize SF_INFO structure
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.samplerate = 44100;
    sfinfo.channels = 1;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the temporary file with libsndfile
    sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 0);
    if (sndfile == NULL) {
        close(fd);
        return 0;
    }

    // Cast the data to a float buffer
    buffer = (float *)data;
    frames = (sf_count_t)(size / sizeof(float));

    // Call the function-under-test
    sf_writef_float(sndfile, buffer, frames);

    // Close the SNDFILE and clean up
    sf_close(sndfile);
    close(fd);
    unlink(tmpl);

    return 0;
}