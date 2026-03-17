#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"
#include <stdio.h>
#include <fcntl.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    GF_ISOOpenMode mode;

    // Ensure the size is sufficient for processing
    if (size < sizeof(GF_ISOOpenMode)) {
        return 0;
    }

    // Initialize the mode from the input data
    mode = *(GF_ISOOpenMode *)data;

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gf_isom_open

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of gf_isom_open
    movie = gf_isom_open(tmpl, mode, (const char *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (movie != NULL) {
        // Call the function-under-test
        gf_isom_can_access_movie(movie, mode);

        // Clean up
        gf_isom_close(movie);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}