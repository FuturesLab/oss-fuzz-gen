#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure we have enough data to initialize parameters
    if (size < sizeof(GF_ISOTrackID) + sizeof(u32) * 2 + sizeof(u8) + sizeof(u16) + sizeof(Bool)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract parameters from the input data
    GF_ISOTrackID TrackID = *((GF_ISOTrackID *)data);
    data += sizeof(GF_ISOTrackID);
    size -= sizeof(GF_ISOTrackID);

    GF_ISOSample sample;
    sample.data = (u8 *)data;
    sample.dataLength = size;

    u32 DescIndex = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    u32 Duration = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    u8 PaddingBits = *data;
    data += sizeof(u8);
    size -= sizeof(u8);

    u16 DegradationPriority = *((u16 *)data);
    data += sizeof(u16);
    size -= sizeof(u16);

    Bool redundant_coding = *((Bool *)data);

    // Call the function under test
    gf_isom_fragment_add_sample(movie, TrackID, &sample, DescIndex, Duration, PaddingBits, DegradationPriority, redundant_coding);

    // Clean up
    gf_isom_close(movie);

    return 0;
}