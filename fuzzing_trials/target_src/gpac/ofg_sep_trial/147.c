#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Initialize trackNumber to a non-zero value

    // Ensure the data size is sufficient to create a file
    if (size < 4) {
        return 0;
    }

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO file from the temporary file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (the_file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_ipod_compatible(the_file, trackNumber);

    // Cleanup
    gf_isom_close(the_file);
    unlink(tmpl);

    return 0;
}