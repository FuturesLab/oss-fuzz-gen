#include <sndfile.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h> // For write, close

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        return 0;
    }

    // Prepare buffer for reading samples
    sf_count_t frames_to_read = 1024; // Arbitrary number of frames to read
    int *buffer = static_cast<int *>(malloc(frames_to_read * sfinfo.channels * sizeof(int)));
    if (buffer == NULL) {
        sf_close(sndfile);
        return 0;
    }

    // Call the function-under-test
    sf_count_t frames_read = sf_readf_int(sndfile, buffer, frames_to_read);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}