#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Include the necessary headers for GF_ISOFile and related functions
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL); // Open a dummy file for testing
    if (!file) {
        return 0; // Exit if file cannot be opened
    }

    Bool root_meta = true; // Set a default boolean value
    u32 track_num = 1; // Example track number
    u32 item_id = 1; // Example item ID
    Bool keep_refs = false; // Set a default boolean value

    // Ensure the data is not empty before using it for keep_props
    const char *keep_props = (size > 0) ? (const char *)data : "default";

    // Call the function-under-test
    gf_isom_remove_meta_item(file, root_meta, track_num, item_id, keep_refs, keep_props);

    // Clean up and close the file
    gf_isom_close(file);

    return 0;
}