#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize with a valid track number

    // Create a temporary ISO file from the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the temporary ISO file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_remove_track(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}