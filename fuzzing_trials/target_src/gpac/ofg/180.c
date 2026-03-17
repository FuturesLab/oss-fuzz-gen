#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // For close() and write()
#include <stdio.h>  // For remove()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1;  // Initialize with a non-zero value
    u32 sampleNumber = 1; // Initialize with a non-zero value

    // Check if the size is sufficient for creating a movie
    if (size < 8) {
        return 0;
    }

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the ISO media file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_remove_sample(movie, trackNumber, sampleNumber);

    // Close and clean up
    gf_isom_close(movie);
    remove(tmpl);

    return 0;
}