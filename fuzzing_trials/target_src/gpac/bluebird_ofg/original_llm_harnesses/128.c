#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Initialize the necessary variables
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    Bool root_meta = GF_TRUE; // or GF_FALSE, try both
    u32 track_num = 1; // Assuming the file has at least one track
    u32 from_id = 1; // Starting ID for the item reference
    u32 type = 0; // Type of the item reference, can try different values

    // Ensure the file is opened successfully
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_meta_get_item_ref_count(file, root_meta, track_num, from_id, type);

    // Close the file after the test
    gf_isom_close(file);

    return 0;
}