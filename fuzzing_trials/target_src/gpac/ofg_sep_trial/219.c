#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract parameters
    if (size < sizeof(u32) * 2 + sizeof(bin128)) {
        return 0;
    }

    // Initialize parameters for gf_isom_remove_user_data
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    u32 UserDataType = *((u32 *)(data + sizeof(u32)));
    bin128 UUID;
    memcpy(UUID, data + 2 * sizeof(u32), sizeof(bin128));

    // Call the function-under-test
    gf_isom_remove_user_data(movie, trackNumber, UserDataType, UUID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}