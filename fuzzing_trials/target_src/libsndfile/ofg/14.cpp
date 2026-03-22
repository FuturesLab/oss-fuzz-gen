#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close() and write()
#include <fcntl.h>   // Include for mkstemp()

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a sound file
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
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (!sndfile) {
        remove(tmpl);
        return 0;
    }

    // Prepare a buffer for the sf_command function
    int command = 0; // Example command, can be varied
    int buffer_size = 256; // Example buffer size
    void *buffer = malloc(buffer_size);
    if (!buffer) {
        sf_close(sndfile);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_command(sndfile, command, buffer, buffer_size);

    // Cleanup
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}