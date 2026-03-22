#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Close the file descriptor
    close(fd);

    // Prepare SF_INFO structure
    SF_INFO sfinfo;
    sfinfo.format = 0; // Ensure it is initialized

    // Attempt to open the file with sf_open
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);

    // If the file was successfully opened, close it
    if (sndfile != NULL) {
        sf_close(sndfile);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}