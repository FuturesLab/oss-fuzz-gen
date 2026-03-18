#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and unlink()
#include <fcntl.h>  // Include for mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Initialize with a non-zero value
    u32 nb_samples = 1;  // Initialize with a non-zero value

    // Check if the input size is sufficient to create a file
    if (size > 0) {
        // Create a temporary file to load the ISO media
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd == -1) {
            return 0;
        }

        // Write the data to the temporary file
        if (write(fd, data, size) != size) {
            close(fd);
            return 0;
        }

        // Close the file descriptor
        close(fd);

        // Open the ISO media file
        the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);

        // Remove the temporary file
        unlink(tmpl);
    }

    if (the_file != NULL) {
        // Call the function-under-test
        gf_isom_purge_samples(the_file, trackNumber, nb_samples);

        // Close the ISO media file
        gf_isom_close(the_file);
    }

    return 0;
}