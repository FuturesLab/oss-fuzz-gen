#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include internal development headers for access to low-level functions

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    Bool root_meta = 1; // Using a non-zero value for Bool
    u32 track_num = 1;  // Example track number
    u32 to_id = 1;      // Example ID
    u32 type = 1;       // Example type

    // Use a different method to create or open an ISO file for fuzzing
    file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL); // Open an empty ISO file for reading
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_meta_item_has_ref(file, root_meta, track_num, to_id, type);

    // Clean up
    gf_isom_close(file);

    return 0;
}