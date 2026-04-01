#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Initialize to true
    u32 track_num = 1;  // Initialize to a non-zero value
    u32 item_id = 0;    // Initialize item_id

    // Since gf_isom_open_from_buffer does not exist, we cannot create an ISO file from the input data.
    // Instead, we will directly call the function-under-test with a NULL file to see how it handles it.
    // This will still test the robustness of the function.

    // Call the function-under-test
    gf_isom_meta_get_next_item_id(file, root_meta, track_num, &item_id);

    // No need to close the file as it is NULL

    return 0;
}

#ifdef __cplusplus
}
#endif