#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1; // Example track number
    u32 UserDataType = 0x75736572; // 'user' in hex
    bin128 UUID;
    memset(UUID, 0, sizeof(UUID)); // Initialize UUID to zero

    // Ensure data is not NULL and has a valid length
    u8 *userData = (u8 *)malloc(size);
    if (!userData) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(userData, data, size);
    u32 DataLength = (u32)size;

    // Call the function-under-test
    gf_isom_add_user_data(movie, trackNumber, UserDataType, UUID, userData, DataLength);

    // Clean up
    free(userData);
    gf_isom_close(movie);

    return 0;
}