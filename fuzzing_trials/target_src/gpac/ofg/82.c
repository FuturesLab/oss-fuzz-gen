#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strdup
#include <gpac/isomedia.h>

// Define Bool if not defined by the included headers
#ifndef Bool
#define Bool int
#endif

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    Bool root_meta;
    u32 track_num, to_id, type;

    // Ensure the size is sufficient to extract parameters
    if (size < sizeof(Bool) + 3 * sizeof(u32) + 1) { // +1 for null-terminator
        return 0;
    }

    // Create a null-terminated string from the input data
    char *file_path = (char *)malloc(size + 1);
    if (!file_path) {
        return 0;
    }
    memcpy(file_path, data, size);
    file_path[size] = '\0'; // Null-terminate the string

    // Open the ISO file using the null-terminated string
    file = gf_isom_open(file_path, GF_ISOM_OPEN_READ, NULL);
    free(file_path); // Free the allocated memory for the file path

    if (!file) {
        return 0; // If the file cannot be opened, exit early
    }

    // Extract parameters from the input data
    root_meta = (Bool)data[0];
    track_num = ((u32)data[1] << 24) | ((u32)data[2] << 16) | ((u32)data[3] << 8) | (u32)data[4];
    to_id = ((u32)data[5] << 24) | ((u32)data[6] << 16) | ((u32)data[7] << 8) | (u32)data[8];
    type = ((u32)data[9] << 24) | ((u32)data[10] << 16) | ((u32)data[11] << 8) | (u32)data[12];

    // Call the function-under-test
    gf_isom_meta_item_has_ref(file, root_meta, track_num, to_id, type);

    // Clean up
    gf_isom_close(file);

    return 0;
}