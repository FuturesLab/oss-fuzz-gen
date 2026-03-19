#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <unistd.h> // Include for close and write functions

extern "C" {
    #include <unistd.h> // Ensure unistd.h is wrapped in extern "C" for C functions
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a sound file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile != NULL) {
        // Call the function-under-test
        sf_close(sndfile);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}