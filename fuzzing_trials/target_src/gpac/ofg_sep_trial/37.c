#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close() and remove()
#include <fcntl.h>  // For mkstemp()

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Initialize with a default track number
    u32 index = 0; // Initialize with a default index
    char *scheme = NULL;
    char *value = NULL;

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the ISO file using the temporary file path
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (the_file) {
        // Call the function-under-test
        gf_isom_get_track_kind(the_file, trackNumber, index, &scheme, &value);

        // Clean up
        gf_isom_close(the_file);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}