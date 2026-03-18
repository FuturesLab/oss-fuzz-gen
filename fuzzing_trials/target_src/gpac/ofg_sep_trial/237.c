#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_237(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract necessary data
    if (size < sizeof(bin128) + sizeof(uint32_t) * 3) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1;  // Example track number
    u32 UserDataType = 0;  // Example user data type

    // Extract UUID from data
    bin128 UUID;
    memcpy(UUID, data, sizeof(bin128));

    // Extract additional data for user data
    u8 *userData = (u8 *)(data + sizeof(bin128));
    u32 DataLength = size - sizeof(bin128);

    // Call the function-under-test
    gf_isom_add_user_data(movie, trackNumber, UserDataType, UUID, userData, DataLength);

    // Clean up
    gf_isom_close(movie);

    return 0;
}