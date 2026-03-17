#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h" // Include this header for u32 and u64 definitions

int LLVMFuzzerTestOneInput_235(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming there's at least one track
    u64 ctime = 0;
    u64 mtime = 0;

    if (size >= sizeof(u64) * 2) {
        ctime = *((u64 *)data);
        mtime = *((u64 *)(data + sizeof(u64)));
    }

    gf_isom_set_media_creation_time(movie, trackNumber, ctime, mtime);

    gf_isom_close(movie);
    return 0;
}