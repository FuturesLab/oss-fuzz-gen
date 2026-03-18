#include <gpac/isomedia.h>
#include <stdint.h>
#include <stddef.h>
#include <gpac/setup.h>

// Function prototype for the function-under-test
// Correct the function prototype to match the declaration in gpac/isomedia.h
GF_Err gf_isom_remove_meta_xml(GF_ISOFile *isom_file, Bool root_meta, u32 track_num);

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract necessary parameters
    if (size < sizeof(Bool) + sizeof(u32)) {
        return 0;
    }

    // Initialize the GF_ISOFile structure
    // Provide a valid temporary directory path as the third argument
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp"); // Open a new GF_ISOFile
    if (!file) {
        return 0;
    }

    // Extract the Bool root_meta from the input data
    Bool root_meta = (Bool)data[0];

    // Extract the u32 track_num from the input data
    u32 track_num = *(u32 *)(data + 1);

    // Call the function-under-test
    gf_isom_remove_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);

    return 0;
}