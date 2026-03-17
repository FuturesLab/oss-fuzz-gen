#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure that the size is sufficient to extract multiple uint32_t values
    if (size < sizeof(uint32_t) * 5) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract values from the data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t sampleDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    uint32_t average_bitrate = *((uint32_t *)(data + 2 * sizeof(uint32_t)));
    uint32_t max_bitrate = *((uint32_t *)(data + 3 * sizeof(uint32_t)));
    uint32_t decode_buffer_size = *((uint32_t *)(data + 4 * sizeof(uint32_t)));

    // Call the function under test
    gf_isom_update_bitrate(movie, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}