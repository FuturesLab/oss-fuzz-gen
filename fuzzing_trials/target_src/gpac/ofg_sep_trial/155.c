#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include for mkstemp, write, close, and unlink
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    u32 track = 1; // Initialize track with a non-zero value

    // Create a temporary file to use as input for GF_ISOFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_find_od_id_for_track(file, track);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}