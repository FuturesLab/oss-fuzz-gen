#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Define and initialize the SNDFILE and SF_INFO structures
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    
    // Initialize SF_INFO structure
    sfinfo.frames = 0;
    sfinfo.samplerate = 44100; // Standard sample rate
    sfinfo.channels = 2; // Stereo
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // WAV format with PCM 16-bit

    // Create a temporary file to use with libsndfile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "w+b");
    if (!file) {
        close(fd);
        return 0;
    }

    // Open the temporary file with libsndfile
    sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 0);
    if (!sndfile) {
        fclose(file);
        return 0;
    }

    // Prepare the buffer for writing
    const int *buffer = reinterpret_cast<const int *>(data);
    sf_count_t frames = size / (sfinfo.channels * sizeof(int));

    // Call the function-under-test
    sf_writef_int(sndfile, buffer, frames);

    // Clean up
    sf_close(sndfile);
    fclose(file);
    remove(tmpl);

    return 0;
}