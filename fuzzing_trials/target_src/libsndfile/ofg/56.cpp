#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an audio file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_WRITE, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare an array of integers to write
    int sample_data[10];
    for (int i = 0; i < 10; ++i) {
        sample_data[i] = i + 1;  // Initialize with some non-zero values
    }

    // Call the function-under-test
    sf_count_t frames_written = sf_write_int(sndfile, sample_data, 10);

    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}