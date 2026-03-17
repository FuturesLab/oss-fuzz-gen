#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

// Declare the fuzzing function
int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the size is sufficient for the test
    if (size < sizeof(GF_ISOTrackID) + sizeof(u8) + sizeof(u32)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract the TrackID, data_size, and PaddingBits from the input data
    GF_ISOTrackID TrackID = *((GF_ISOTrackID *)data);
    data += sizeof(GF_ISOTrackID);
    size -= sizeof(GF_ISOTrackID);

    u32 data_size = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    u8 PaddingBits = *data;
    data += sizeof(u8);
    size -= sizeof(u8);

    // Ensure data_size does not exceed the remaining size
    if (data_size > size) {
        data_size = size;
    }

    // Call the function-under-test
    gf_isom_fragment_append_data(movie, TrackID, (u8 *)data, data_size, PaddingBits);

    // Clean up
    gf_isom_close(movie);

    return 0;
}