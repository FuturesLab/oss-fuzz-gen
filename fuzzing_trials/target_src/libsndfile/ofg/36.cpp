#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for write and close functions

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Temporary file setup
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the file with libsndfile for reading
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        remove(tmpl);
        return 0;
    }

    // Prepare a buffer to read data into
    size_t buffer_size = 1024;
    short *buffer = (short *)malloc(buffer_size * sizeof(short));
    if (buffer == NULL) {
        sf_close(sndfile);
        remove(tmpl);
        return 0;
    }

    // Attempt to read frames from the file
    sf_count_t frames_read = sf_readf_short(sndfile, buffer, buffer_size);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}