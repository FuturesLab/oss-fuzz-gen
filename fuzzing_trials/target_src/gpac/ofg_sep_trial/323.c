#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_323(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for the parameters
    if (size < sizeof(bin128) + sizeof(uint32_t) + 1) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from data
    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Extract UUID from data
    bin128 UUID;
    memcpy(UUID, data, sizeof(bin128));
    data += sizeof(bin128);
    size -= sizeof(bin128);

    // Remaining data is used for data parameter
    const uint8_t *uuid_data = data;
    uint32_t data_size = size;

    // Call the function-under-test
    gf_isom_add_uuid(movie, trackNumber, UUID, uuid_data, data_size);

    // Close the ISO file
    gf_isom_close(movie);

    return 0;
}