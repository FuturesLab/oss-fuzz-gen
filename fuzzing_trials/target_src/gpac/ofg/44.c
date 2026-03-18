#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;  // A valid track number
    u64 timestamp = 0;    // Start timestamp
    char *name = (char *)malloc(size + 1);

    if (name == NULL || movie == NULL) {
        if (movie != NULL) {
            gf_isom_close(movie);
        }
        return 0;
    }

    // Copy data to name and null-terminate it
    memcpy(name, data, size);
    name[size] = '\0';

    // Call the function-under-test
    gf_isom_add_chapter(movie, trackNumber, timestamp, name);

    // Clean up
    free(name);
    gf_isom_close(movie);

    return 0;
}