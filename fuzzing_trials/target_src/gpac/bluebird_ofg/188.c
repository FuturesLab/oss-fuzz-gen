#include <stdint.h>
#include <stddef.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    Bool root_meta = 1; // True
    u32 track_num = 1;
    u32 from_id = 1;
    u32 to_id = 2;
    u32 type = 0;
    u64 ref_index = 0;

    // Ensure the file is not NULL
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_meta_add_item_ref(file, root_meta, track_num, from_id, to_id, type, &ref_index);

    // Close the file
    gf_isom_close(file);

    return 0;
}