#include <stdint.h>
#include <stdlib.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (file == NULL) {
        return 0;
    }

    // Ensure that the size is sufficient to extract the required parameters
    if (size < 20) {
        gf_isom_close(file);
        return 0;
    }

    // Extract parameters from the input data
    Bool root_meta = (Bool)data[0];
    u32 track_num = *((u32 *)(data + 1));
    u32 item_id = *((u32 *)(data + 5));
    u32 group_id = *((u32 *)(data + 9));
    u32 group_type = *((u32 *)(data + 13));

    // Call the function-under-test
    gf_isom_meta_add_item_group(file, root_meta, track_num, item_id, group_id, group_type);

    // Clean up
    gf_isom_close(file);

    return 0;
}