#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Create a temporary buffer with an additional byte for the null terminator
    char *temp_data = (char *)malloc(size + 1);
    if (!temp_data) {
        return 0; // If memory allocation fails, exit
    }

    // Copy the input data to the temporary buffer and null terminate it
    memcpy(temp_data, data, size);
    temp_data[size] = '\0';

    // Declare and initialize variables
    GF_ISOFile *file = gf_isom_open(temp_data, GF_ISOM_OPEN_READ, NULL);
    free(temp_data); // Free the temporary buffer
    if (!file) {
        return 0; // If file opening fails, exit
    }

    Bool root_meta = 1; // Initialize with a non-null value
    u32 track_num = 1; // Initialize with a non-null value
    u32 item_id = 1; // Initialize with a non-null value
    u8 *out_data = NULL;
    u32 out_size = 0;
    u32 out_alloc_size = 0;
    const char *out_mime = NULL;
    Bool use_annex_b = 0; // Initialize with a non-null value

    // Call the function-under-test
    gf_isom_extract_meta_item_mem(file, root_meta, track_num, item_id, &out_data, &out_size, &out_alloc_size, &out_mime, use_annex_b);

    // Clean up
    if (out_data) {
        free(out_data);
    }

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_freeze_order
    gf_isom_freeze_order(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}