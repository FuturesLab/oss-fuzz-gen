#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    Bool root_meta;
    u32 track_num, from_id, type;

    // Initialize the parameters
    file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Ensure the data size is sufficient to extract parameters
    if (size < sizeof(u32) * 3 + sizeof(Bool)) {
        gf_isom_close(file);
        return 0;
    }

    // Extract parameters from the data
    root_meta = (Bool)data[0];
    track_num = *((u32 *)(data + 1));
    from_id = *((u32 *)(data + 1 + sizeof(u32)));
    type = *((u32 *)(data + 1 + 2 * sizeof(u32)));

    // Call the function-under-test
    gf_isom_meta_get_item_ref_count(file, root_meta, track_num, from_id, type);

    // Clean up
    gf_isom_close(file);

    return 0;
}