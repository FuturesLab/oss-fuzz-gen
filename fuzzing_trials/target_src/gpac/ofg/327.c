#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    Bool last_segment = GF_FALSE;

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl); // Ensure the temporary file is removed
        return 0; // Unable to write data to the file
    }
    close(fd);

    // Open the ISO file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(tmpl); // Ensure the temporary file is removed
        return 0; // Unable to open ISO file
    }

    // Fuzz the function
    gf_isom_flush_fragments(movie, last_segment);

    // Clean up
    gf_isom_close(movie);
    unlink(tmpl); // Remove the temporary file

    return 0;
}