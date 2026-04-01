#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for 'close'

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Temporary file setup
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

    // Write the input data to the temporary file
    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 0);
    if (!sndfile) {
        fclose(file);
        return 0;
    }

    // Prepare double array for writing
    const size_t max_samples = 1024;
    double samples[max_samples];
    for (size_t i = 0; i < max_samples; ++i) {
        samples[i] = (double)(data[i % size]) / 255.0; // Normalize data to double
    }

    // Call the function under test
    sf_count_t frames_written = sf_writef_double(sndfile, samples, max_samples);

    // Clean up
    sf_close(sndfile);
    fclose(file);
    remove(tmpl);

    return 0;
}