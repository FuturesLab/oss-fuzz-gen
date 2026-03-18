#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    // Ensure that the size is sufficient to extract values for track_num and metaType
    if (size < 8) {
        gf_isom_close(file);
        return 0;
    }

    // Extract track_num and metaType from the input data
    u32 track_num = *((u32*)data);
    u32 metaType = *((u32*)(data + 4));

    // Use a non-zero value for root_meta
    Bool root_meta = 1;

    // Call the function under test
    gf_isom_set_meta_type(file, root_meta, track_num, metaType);

    // Clean up
    gf_isom_close(file);
    return 0;
}

#ifdef __cplusplus
}
#endif