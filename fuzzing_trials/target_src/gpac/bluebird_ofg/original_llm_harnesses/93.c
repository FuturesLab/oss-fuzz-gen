#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract parameters
    if (size < sizeof(u32) * 2 + sizeof(u64) * 2 + sizeof(GF_ISOEditType)) {
        return 0;
    }

    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = *(const u32 *)(data);
    u32 seg_index = *(const u32 *)(data + sizeof(u32));
    u64 EditDuration = *(const u64 *)(data + sizeof(u32) * 2);
    u64 MediaTime = *(const u64 *)(data + sizeof(u32) * 2 + sizeof(u64));
    GF_ISOEditType EditMode = *(const GF_ISOEditType *)(data + sizeof(u32) * 2 + sizeof(u64) * 2);

    // Call the function under test
    gf_isom_modify_edit(movie, trackNumber, seg_index, EditDuration, MediaTime, EditMode);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}