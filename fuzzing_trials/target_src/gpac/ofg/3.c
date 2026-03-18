#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        return 0;
    }

    // Simulate feeding data into the file structure
    // This part is hypothetical and depends on the actual API available for GF_ISOFile
    // Since we do not have the actual function, we assume a placeholder function
    // Example: gf_isom_feed_data(file, (char *)data, size);

    Bool root_meta = (size % 2 == 0) ? GF_TRUE : GF_FALSE;
    u32 track_num = (size > 4) ? *(u32 *)(data + 0) : 1;
    u32 item_id = (size > 8) ? *(u32 *)(data + 4) : 1;

    gf_isom_set_meta_primary_item(file, root_meta, track_num, item_id);

    gf_isom_close(file);
    return 0;
}