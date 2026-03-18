#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize to a non-zero value
    u32 sampleNumber = 1; // Initialize to a non-zero value

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO media file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        unlink(tmpl);
        return 0;
    }

    // Call the function under test
    gf_isom_remove_sample(movie, trackNumber, sampleNumber);

    // Clean up
    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}