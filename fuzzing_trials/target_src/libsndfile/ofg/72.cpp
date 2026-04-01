#include <stdint.h>
#include <stdlib.h>
#include <sndfile.h>
#include <unistd.h> // Include for close() and unlink()

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;

    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 0);
    if (sndfile == NULL) {
        close(fd);
        return 0; // Failed to open the file with libsndfile
    }

    // Call the function-under-test
    sf_count_t frames_written = sf_write_raw(sndfile, data, (sf_count_t)size);

    // Clean up
    sf_close(sndfile);
    close(fd);
    unlink(tmpl); // Remove the temporary file

    return 0;
}