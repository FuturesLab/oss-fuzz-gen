#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is sufficient for extracting parameters
    if (size < sizeof(uint32_t) + sizeof(uint64_t) * 3 + sizeof(uint32_t)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract parameters from the input data
    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    uint64_t EditTime = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    uint64_t EditDuration = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    uint64_t MediaTime = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    uint32_t media_rate = *(uint32_t *)data;

    // Call the function-under-test
    gf_isom_set_edit_with_rate(movie, trackNumber, EditTime, EditDuration, MediaTime, media_rate);

    // Clean up
    gf_isom_close(movie);

    return 0;
}