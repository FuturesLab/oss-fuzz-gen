#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Instead of using gf_isom_open_from_buffer, we use gf_isom_open to open a temporary file
    // Create a temporary file
    char filename[] = "/tmp/fuzz_inputXXXXXX";
    int fd = mkstemp(filename);
    if (fd < 0) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO file using the temporary file
    GF_ISOFile *movie = gf_isom_open(filename, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(filename);
        return 0;
    }

    u32 trackNumber = 1; // Assuming track number 1 for testing purposes

    // Call the function-under-test
    gf_isom_add_track_to_root_od(movie, trackNumber);

    // Clean up
    gf_isom_close(movie);
    unlink(filename);

    return 0;
}