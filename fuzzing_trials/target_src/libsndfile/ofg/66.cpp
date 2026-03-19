#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for write, close, and unlink

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);
    
    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (!sndfile) {
        return 0;
    }
    
    // Prepare a buffer to read floats
    sf_count_t frames = 1024; // Arbitrary number of frames to read
    float *buffer = (float *)malloc(frames * sfinfo.channels * sizeof(float));
    if (!buffer) {
        sf_close(sndfile);
        return 0;
    }
    
    // Call the function-under-test
    sf_readf_float(sndfile, buffer, frames);
    
    // Clean up
    free(buffer);
    sf_close(sndfile);
    unlink(tmpl); // Remove the temporary file
    
    return 0;
}