#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for 'write', 'close', and 'mkstemp' functions

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Temporary file creation
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // If writing fails, exit early
    }

    // Close the file descriptor
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        return 0; // If opening the file fails, exit early
    }

    // Prepare a buffer for the command
    int command = SFC_GET_CURRENT_SF_INFO;
    void *buffer = malloc(sizeof(SF_INFO));
    if (buffer == NULL) {
        sf_close(sndfile);
        return 0; // If memory allocation fails, exit early
    }

    // Call the function-under-test
    sf_command(sndfile, command, buffer, sizeof(SF_INFO));

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl); // Remove the temporary file

    return 0;
}