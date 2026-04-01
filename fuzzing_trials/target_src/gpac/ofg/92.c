#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract parameters
    if (size < sizeof(uint32_t) * 3 + sizeof(uint64_t) * 2 + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize parameters
    GF_ISOFile *movie = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL); // Open a test file
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);

    u32 seg_index = *((u32 *)data);
    data += sizeof(u32);

    u64 EditDuration = *((u64 *)data);
    data += sizeof(u64);

    u64 MediaTime = *((u64 *)data);
    data += sizeof(u64);

    GF_ISOEditType EditMode = *((GF_ISOEditType *)data);

    // Fuzz the function
    gf_isom_modify_edit(movie, trackNumber, seg_index, EditDuration, MediaTime, EditMode);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}