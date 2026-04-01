#include <stdint.h>
#include <stdlib.h>
#include <sndfile.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an audio file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) == -1) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a sound file
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_write_sync(sndfile);

    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}