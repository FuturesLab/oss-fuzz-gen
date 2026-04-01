#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/tools.h>
#include <string.h>

int LLVMFuzzerTestOneInput_324(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Example track number
    bin128 UUID;
    const u8 *uuid_data = data;
    u32 data_size = size;

    // Ensure UUID is properly sized
    if (size < 16) {
        return 0;
    }

    // Copy the first 16 bytes of data into the UUID
    memcpy(UUID, uuid_data, 16);

    // Call the function-under-test
    gf_isom_add_uuid(movie, trackNumber, UUID, data, data_size);

    // Clean up
    gf_isom_close(movie);

    return 0;
}