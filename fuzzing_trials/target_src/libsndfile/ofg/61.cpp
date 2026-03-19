#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Temporary file creation
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor as sf_open will open it again
    close(fd);

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    sfinfo.frames = 0;
    sfinfo.samplerate = 44100; // Common sample rate
    sfinfo.channels = 2;       // Stereo
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Common format
    sfinfo.sections = 0;
    sfinfo.seekable = 0;

    // Open the sound file
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);

    // Clean up
    if (sndfile != NULL) {
        sf_close(sndfile);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}