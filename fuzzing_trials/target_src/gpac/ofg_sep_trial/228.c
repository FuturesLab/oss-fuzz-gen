#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize with a non-zero track number

    // Create a temporary file to hold the input data
    char tmp_file_name[] = "/tmp/fuzz_input.XXXXXX";
    int fd = mkstemp(tmp_file_name);
    if (fd == -1) {
        return 0; // Exit if the temporary file could not be created
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmp_file_name);
        return 0; // Exit if the data could not be written completely
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO file using the temporary file
    movie = gf_isom_open(tmp_file_name, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(tmp_file_name);
        return 0; // Exit if the movie could not be created
    }

    // Call the function-under-test
    gf_isom_add_track_to_root_od(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);
    unlink(tmp_file_name);

    return 0;
}