#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = GF_FALSE;
    u32 track_num = 0;

    // Use a minimum size check that makes sense for the operation
    if (size < 4) {
        return 0;
    }

    // Instead of opening from buffer, let's assume creating a new empty ISOFile for testing
    file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    // Set root_meta and track_num based on available data
    if (size > 4) {
        root_meta = (Bool)(data[4] % 2);
    }
    if (size > 5) {
        track_num = (u32)data[5];
    }

    // Call the function-under-test
    gf_isom_get_meta_item_count(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);

    return 0;
}