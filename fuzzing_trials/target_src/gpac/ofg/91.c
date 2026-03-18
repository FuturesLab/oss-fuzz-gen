#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    u64 ctime, mtime;

    // Ensure the data size is sufficient for u64 values
    if (size < 2 * sizeof(u64)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract the ctime and mtime values from the input data
    ctime = *((u64 *)data);
    mtime = *((u64 *)(data + sizeof(u64)));

    // Call the function-under-test
    gf_isom_set_creation_time(movie, ctime, mtime);

    // Clean up
    gf_isom_close(movie);

    return 0;
}