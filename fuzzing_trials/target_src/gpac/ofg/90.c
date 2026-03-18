#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u64 ctime = 0;
    u64 mtime = 0;

    // Ensure size is sufficient to extract u64 values
    if (size < sizeof(u64) * 2) {
        return 0;
    }

    // Initialize u64 values from the input data
    ctime = *(const u64 *)data;
    mtime = *(const u64 *)(data + sizeof(u64));

    // Create a dummy movie object for testing with a valid file path
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_creation_time(movie, ctime, mtime);

    // Clean up
    gf_isom_close(movie);

    return 0;
}