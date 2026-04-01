#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber;

    // Ensure size is large enough to extract a track number
    if (size < sizeof(u32)) {
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
    if (!movie) {
        unlink(tmpl);
        return 0;
    }

    // Extract track number from the data
    trackNumber = *((u32 *)data);

    // Call the function-under-test
    gf_isom_remove_track(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}