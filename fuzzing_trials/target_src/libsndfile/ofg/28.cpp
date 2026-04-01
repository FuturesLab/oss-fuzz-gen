#include <sndfile.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for close(), unlink(), and write()

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a sound file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as a sound file
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile != NULL) {
        // Call the function-under-test
        const char *error_message = sf_strerror(sndfile);
        if (error_message != NULL) {
            printf("Error message: %s\n", error_message);
        }
        sf_close(sndfile);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}