#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    Bool leave_empty;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;

    // Create a temporary ISO file for fuzzing
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Try different values for leave_empty
    leave_empty = GF_FALSE;
    gf_isom_reset_alt_brands_ex(movie, leave_empty);

    leave_empty = GF_TRUE;
    gf_isom_reset_alt_brands_ex(movie, leave_empty);

    // Clean up
    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}