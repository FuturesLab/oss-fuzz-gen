#include <sndfile.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this header for the 'close' function

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Define and initialize variables before any goto statements
    SNDFILE *sndfile = nullptr;
    SF_INFO sfinfo;
    int *buffer = nullptr;
    sf_count_t frames = 0;

    // Ensure size is sufficient for at least one frame
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize SF_INFO structure
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Create a temporary file to use with libsndfile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file with libsndfile
    sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (sndfile == nullptr) {
        close(fd);
        return 0;
    }

    // Calculate the number of frames
    frames = size / sizeof(int);

    // Allocate buffer and copy data
    buffer = (int *)malloc(frames * sizeof(int));
    if (buffer == nullptr) {
        sf_close(sndfile);
        close(fd);
        return 0;
    }
    memcpy(buffer, data, frames * sizeof(int));

    // Call the function-under-test
    sf_writef_int(sndfile, buffer, frames);

    // Cleanup
    free(buffer);
    sf_close(sndfile);
    close(fd);
    remove(tmpl);

    return 0;
}