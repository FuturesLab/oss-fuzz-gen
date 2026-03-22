#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for unlink, write, and close

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    SF_INFO sfinfo;
    SNDFILE *sndfile = NULL;
    int *buffer = NULL;
    sf_count_t frames = 0;

    // Ensure the input data is sufficient to be processed as an audio file
    if (size < 44) { // Minimum size for a valid WAV header
        return 0;
    }

    // Create a temporary file to write the input data
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

    // Close the file descriptor so it can be used by sf_open
    close(fd);

    // Open the temporary file as a sound file
    sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl); // Ensure the temporary file is removed
        return 0;
    }

    // Allocate buffer for reading
    frames = sfinfo.frames;
    buffer = (int *)malloc(frames * sfinfo.channels * sizeof(int));
    if (buffer == NULL) {
        sf_close(sndfile);
        unlink(tmpl); // Ensure the temporary file is removed
        return 0;
    }

    // Call the function-under-test
    sf_read_int(sndfile, buffer, frames);

    // Clean up
    sf_close(sndfile);
    free(buffer);
    unlink(tmpl);

    return 0;
}