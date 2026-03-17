#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    char segName[256];
    if (size > 0) {
        size_t copy_size = size < sizeof(segName) - 1 ? size : sizeof(segName) - 1;
        memcpy(segName, data, copy_size);
        segName[copy_size] = '\0';
    } else {
        strcpy(segName, "default_segment");
    }

    Bool memory_mode = (size % 2 == 0) ? GF_FALSE : GF_TRUE;

    gf_isom_start_segment(movie, segName, memory_mode);

    gf_isom_close(movie);

    return 0;
}