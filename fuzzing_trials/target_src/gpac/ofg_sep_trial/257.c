#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    // Ensure there is enough data for all parameters
    if (size < sizeof(u32) * 2 + sizeof(u64) * 2 + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize parameters from data
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *((u32*)data);
    u32 seg_index = *((u32*)(data + sizeof(u32)));
    u64 EditDuration = *((u64*)(data + sizeof(u32) * 2));
    u64 MediaTime = *((u64*)(data + sizeof(u32) * 2 + sizeof(u64)));
    GF_ISOEditType EditMode = *((GF_ISOEditType*)(data + sizeof(u32) * 2 + sizeof(u64) * 2));

    // Call the function under test
    gf_isom_modify_edit(movie, trackNumber, seg_index, EditDuration, MediaTime, EditMode);

    // Clean up
    gf_isom_close(movie);

    return 0;
}