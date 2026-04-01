#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

// Ensure the necessary types are defined
typedef uint64_t u64;

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract the required parameters
    if (size < sizeof(u64) + sizeof(Bool)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract the u64 duration from the data
    u64 duration = *((u64 *)data);

    // Extract the Bool remove_mehd from the data
    Bool remove_mehd = *((Bool *)(data + sizeof(u64)));

    // Call the function-under-test
    gf_isom_set_movie_duration(movie, duration, remove_mehd);

    // Clean up
    gf_isom_close(movie);

    return 0;
}