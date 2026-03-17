#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(movie);
        return 0;
    }

    if (size > 0) {
        write(fd, data, size);
    }
    close(fd);

    gf_isom_set_final_name(movie, tmpl);

    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}