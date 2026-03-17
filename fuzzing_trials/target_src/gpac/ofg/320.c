#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(movie);
        return 0;
    }
    close(fd);

    FILE *file = fopen(tmpl, "wb");
    if (!file) {
        gf_isom_close(movie);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    u64 start_range = 0;
    u64 end_range = size > 0 ? (u64)size - 1 : 0;
    GF_ISOOpenMode flags = GF_ISOM_OPEN_WRITE; // Changed to GF_ISOOpenMode

    gf_isom_open_segment(movie, tmpl, start_range, end_range, flags);

    gf_isom_close(movie);
    remove(tmpl);

    return 0;
}