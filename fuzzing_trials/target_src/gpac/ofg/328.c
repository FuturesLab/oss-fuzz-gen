#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    Bool last_segment = GF_FALSE;
    char tmp_filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd;

    // Create a temporary file to write the input data
    fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmp_filename);
        return 0;
    }
    close(fd);

    // Open the ISO file from the temporary file
    movie = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        remove(tmp_filename);
        return 0;
    }

    // Try different values for last_segment
    gf_isom_flush_fragments(movie, last_segment);

    last_segment = GF_TRUE;
    gf_isom_flush_fragments(movie, last_segment);

    // Close the movie to free resources
    gf_isom_close(movie);

    // Remove the temporary file
    remove(tmp_filename);

    return 0;
}