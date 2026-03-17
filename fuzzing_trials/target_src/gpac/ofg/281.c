#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract all parameters
    if (size < sizeof(uint32_t) * 4 + sizeof(uint64_t)) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    Bool root_meta = (data[0] % 2 == 0) ? GF_TRUE : GF_FALSE;
    uint32_t track_num = *((uint32_t *)(data + 1)) % 100;  // Limit track number to 100
    uint32_t from_id = *((uint32_t *)(data + 5)) % 1000;  // Limit from_id to 1000
    uint32_t to_id = *((uint32_t *)(data + 9)) % 1000;    // Limit to_id to 1000
    uint32_t type = *((uint32_t *)(data + 13)) % 10;      // Limit type to 10
    uint64_t ref_index = *((uint64_t *)(data + 17)) % 1000; // Limit ref_index to 1000

    // Call the function-under-test
    gf_isom_meta_add_item_ref(file, root_meta, track_num, from_id, to_id, type, &ref_index);

    // Clean up
    gf_isom_close(file);

    return 0;
}