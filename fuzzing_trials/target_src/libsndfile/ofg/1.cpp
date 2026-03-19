#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and write()

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor to flush the data
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile != NULL) {
        // Call the function-under-test
        sf_perror(sndfile);

        // Close the SNDFILE
        sf_close(sndfile);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}