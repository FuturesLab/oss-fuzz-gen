#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Non-zero value for true
    u32 track_num = 1;  // Initialize with a valid track number
    u32 metaType = 0;   // Initialize with a default meta type

    // Ensure size is sufficient for reading u32 values
    if (size >= sizeof(u32) * 2) {
        track_num = *((u32 *)data); // Extract track_num from data
        metaType = *((u32 *)(data + sizeof(u32))); // Extract metaType from data
    }

    // Initialize the GF_ISOFile structure
    file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);

    // Call the function-under-test
    gf_isom_set_meta_type(file, root_meta, track_num, metaType);

    // Clean up
    if (file != NULL) {
        gf_isom_close(file);
    }

    return 0;
}