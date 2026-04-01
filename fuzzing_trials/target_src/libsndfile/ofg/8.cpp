#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Include for write() and close()
#include <sys/types.h> // Include for ssize_t

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Define a temporary file name
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

    // Close the file descriptor to allow sf_open to work with it
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);

    // Call the function-under-test if the file was opened successfully
    if (sndfile != NULL) {
        sf_write_sync(sndfile);
        sf_close(sndfile);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}