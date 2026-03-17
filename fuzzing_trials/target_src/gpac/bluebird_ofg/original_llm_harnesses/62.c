#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

// Function to initialize a GF_ISOFile
GF_ISOFile* init_gf_isofile() {
    // Use a GPAC library function to create or initialize a GF_ISOFile
    // Assuming there is a function like gf_isom_open_file or similar for initialization
    return gf_isom_open_file(NULL, GF_ISOM_OPEN_WRITE, NULL);
}

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < sizeof(u32) * 3 + sizeof(bin128)) {
        return 0;
    }

    // Initialize parameters
    GF_ISOFile *movie = init_gf_isofile();
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *(u32 *)(data);
    u32 UserDataType = *(u32 *)(data + sizeof(u32));
    bin128 UUID;
    memcpy(UUID, data + 2 * sizeof(u32), sizeof(bin128));
    u32 UserDataIndex = *(u32 *)(data + 2 * sizeof(u32) + sizeof(bin128));

    // Call the function-under-test
    gf_isom_remove_user_data_item(movie, trackNumber, UserDataType, UUID, UserDataIndex);

    // Cleanup
    gf_isom_close(movie);

    return 0;
}