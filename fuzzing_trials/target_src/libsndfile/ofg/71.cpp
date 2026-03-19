#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sndfile.h>

extern "C" {
    #include <unistd.h> // For unlink and close
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Create a temporary file to be used with SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    sfinfo.frames = 0;
    sfinfo.samplerate = 44100; // Common sample rate
    sfinfo.channels = 2;       // Stereo
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Common format

    // Open the file as a SNDFILE
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (!sndfile) {
        fclose(file);
        return 0;
    }

    // Call the function-under-test
    sf_count_t frames_written = sf_write_raw(sndfile, data, static_cast<sf_count_t>(size));

    // Clean up
    sf_close(sndfile);
    fclose(file);
    unlink(tmpl);

    return 0;
}