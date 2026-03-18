#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Initialize with a non-zero track number

    // Create a temporary file and write the input data to it
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO file using the temporary file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (the_file == NULL) {
        unlink(tmpl); // Clean up the temporary file
        return 0;
    }

    // Call the function-under-test
    gf_isom_purge_track_reference(the_file, trackNumber);

    // Clean up
    gf_isom_close(the_file);
    unlink(tmpl); // Clean up the temporary file

    return 0;
}