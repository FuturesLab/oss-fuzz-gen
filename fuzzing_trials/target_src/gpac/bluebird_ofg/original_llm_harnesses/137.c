#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(uint32_t)) {
        // Not enough data to extract two uint32_t values
        return 0;
    }

    // Initialize GF_ISOFile using a library function with the correct number of arguments
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber and index from the data
    uint32_t trackNumber = *(uint32_t *)(data);
    uint32_t index = *(uint32_t *)(data + sizeof(uint32_t));

    // Call the function-under-test
    gf_isom_remove_chapter(movie, trackNumber, index);

    // Clean up
    gf_isom_close(movie);

    return 0;
}