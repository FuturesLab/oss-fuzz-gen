#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and write()
#include <stdio.h>  // Include for remove()
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Example track number, non-zero
    u64 for_time = 0;

    // Check if the input size is sufficient for further processing
    if (size < sizeof(u64)) {
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
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_sample_description_index(movie, trackNumber, for_time);

    // Close the ISO media file
    gf_isom_close(movie);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}