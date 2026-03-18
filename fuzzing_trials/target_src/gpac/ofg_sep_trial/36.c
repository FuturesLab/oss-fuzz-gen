#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>   // For close() and unlink()
#include <fcntl.h>    // For open() and O_* constants
#include <sys/types.h>
#include <sys/stat.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1;
    u32 index = 0;
    char *scheme = NULL;
    char *value = NULL;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as an ISO file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_track_kind(the_file, trackNumber, index, &scheme, &value);

    // Clean up
    gf_isom_close(the_file);
    if (scheme) free(scheme);
    if (value) free(value);

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}