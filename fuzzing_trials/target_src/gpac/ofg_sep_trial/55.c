#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the ISO file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_remove_root_od(movie);

    // Close the ISO file
    gf_isom_close(movie);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}