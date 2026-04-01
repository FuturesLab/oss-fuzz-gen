#include <stdint.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/scenegraph.h>
#include <gpac/tools.h>
#include <gpac/internal/isomedia_dev.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract the parameters
    if (size < sizeof(u32) * 2) {
        return 0;
    }

    // Create a dummy GF_ISOFile object using gf_isom_open
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Extract parameters from the input data
    Bool root_meta = (Bool)(data[0] % 2); // Use first byte for root_meta (either 0 or 1)
    u32 track_num = *((u32 *)(data + 1)); // Use the next 4 bytes for track_num
    u32 item_ID = *((u32 *)(data + 5));   // Use the next 4 bytes for item_ID

    // Call the function-under-test
    gf_isom_get_meta_item_by_id(file, root_meta, track_num, item_ID);

    // Clean up
    gf_isom_close(file);

    return 0;
}