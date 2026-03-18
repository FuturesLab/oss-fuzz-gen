#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize trackNumber to a non-zero value

    // Check if size is sufficient to create a movie
    if (size < 4) {
        return 0;
    }

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO media file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        goto cleanup;
    }

    // Call the function-under-test
    gf_isom_remove_track(movie, trackNumber);

cleanup:
    // Clean up
    if (movie != NULL) {
        gf_isom_close(movie);
    }
    unlink(tmpl); // Remove the temporary file

    return 0;
}