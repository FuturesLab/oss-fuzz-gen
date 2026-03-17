#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_READ, NULL);

    if (!movie) {
        return 0;
    }

    // Ensure the data is large enough to extract trackNumber and duration
    if (size < sizeof(uint32_t) * 2) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and duration from the input data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t duration = *((uint32_t *)(data + sizeof(uint32_t)));

    // Call the function-under-test
    gf_isom_set_last_sample_duration(movie, trackNumber, duration);

    gf_isom_close(movie);
    return 0;
}