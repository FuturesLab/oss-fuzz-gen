#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is large enough to extract necessary parameters
    if (size < sizeof(u32) * 3 + sizeof(bin128)) {
        gf_isom_close(movie);
        return 0;
    }

    u32 trackNumber = *(const u32 *)data;
    data += sizeof(u32);
    size -= sizeof(u32);

    u32 UserDataType = *(const u32 *)data;
    data += sizeof(u32);
    size -= sizeof(u32);

    bin128 UUID;
    memcpy(UUID, data, sizeof(bin128));
    data += sizeof(bin128);
    size -= sizeof(bin128);

    u32 UserDataIndex = *(const u32 *)data;

    // Call the function under test
    gf_isom_remove_user_data_item(movie, trackNumber, UserDataType, UUID, UserDataIndex);

    gf_isom_close(movie);
    return 0;
}