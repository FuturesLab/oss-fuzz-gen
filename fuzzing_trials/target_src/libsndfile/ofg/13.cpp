#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Include for close()
#include <sndfile.h>

// Ensure the C library is properly linked with C++ code
extern "C" {
    sf_count_t sf_write_double(SNDFILE *, const double *, sf_count_t);
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    double *buffer;
    sf_count_t frames;

    // Initialize SF_INFO structure
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;

    // Open a temporary file for writing
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If unable to create temp file, exit
    }
    close(fd);

    // Open the file as a sound file
    sndfile = sf_open(tmpl, SFM_WRITE, &sfinfo);
    if (!sndfile) {
        remove(tmpl);
        return 0; // If unable to open sound file, exit
    }

    // Allocate buffer for double data
    frames = size / sizeof(double);
    buffer = (double *)malloc(frames * sizeof(double));
    if (!buffer) {
        sf_close(sndfile);
        remove(tmpl);
        return 0; // If unable to allocate buffer, exit
    }

    // Copy data into buffer
    for (sf_count_t i = 0; i < frames; ++i) {
        if (i < (sf_count_t)(size / sizeof(double))) {
            buffer[i] = ((const double *)data)[i];
        } else {
            buffer[i] = 0.0; // Fill remaining buffer with zeros if needed
        }
    }

    // Call the function-under-test
    sf_write_double(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}