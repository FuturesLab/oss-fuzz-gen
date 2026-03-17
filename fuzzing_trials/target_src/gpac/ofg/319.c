#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(movie);
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    u64 start_range = 0;
    u64 end_range = size > 0 ? size - 1 : 0;
    GF_ISOOpenMode flags = GF_ISOM_OPEN_READ; // Use the correct type and value

    gf_isom_open_segment(movie, tmpl, start_range, end_range, flags);

    gf_isom_close(movie);
    unlink(tmpl);

    return 0;
}