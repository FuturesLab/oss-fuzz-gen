#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/tools.h>

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the size is sufficient for our needs
    if (size < sizeof(u32) * 2 + sizeof(bin128)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber and UserDataType from the data
    u32 trackNumber = *((u32 *)data);
    u32 UserDataType = *((u32 *)(data + sizeof(u32)));

    // Extract UUID from the data
    bin128 UUID;
    memcpy(UUID, data + sizeof(u32) * 2, sizeof(bin128));

    // Call the function-under-test
    gf_isom_remove_user_data(movie, trackNumber, UserDataType, UUID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}