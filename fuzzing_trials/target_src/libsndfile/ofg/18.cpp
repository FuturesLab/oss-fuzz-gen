#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include for write and close functions
#include <sndfile.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Temporary file path
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    // Ensure the file descriptor is valid
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);

    // Check if the file was opened successfully
    if (sndfile != NULL) {
        // Call the function-under-test
        sf_error(sndfile); // Use the function without assigning to a variable

        // Close the sound file
        sf_close(sndfile);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}