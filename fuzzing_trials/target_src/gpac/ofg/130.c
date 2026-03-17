#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure the duration is within a reasonable range
    u64 duration = 0;
    if (size >= sizeof(u64)) {
        duration = *((u64 *)data);
    }

    // Ensure remove_mehd is a valid Bool value
    Bool remove_mehd = (size > sizeof(u64)) ? (Bool)(data[sizeof(u64)] % 2) : GF_FALSE;

    // Call the function-under-test
    gf_isom_set_movie_duration(movie, duration, remove_mehd);

    // Clean up
    gf_isom_close(movie);

    return 0;
}