#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

// Include the standard library for file operations
#include <stdio.h>

// Define the function without the C++ specific extern "C"
int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract parameters
    if (size < 24) {
        return 0;
    }

    // Create two GF_ISOFile objects
    GF_ISOFile *f1 = gf_isom_open("dummy1.mp4", GF_ISOM_OPEN_READ, NULL);
    GF_ISOFile *f2 = gf_isom_open("dummy2.mp4", GF_ISOM_OPEN_READ, NULL);

    if (!f1 || !f2) {
        // If file opening fails, clean up and return
        if (f1) gf_isom_close(f1);
        if (f2) gf_isom_close(f2);
        return 0;
    }

    // Extract parameters from the input data
    uint32_t tk1 = *(const uint32_t *)(data);
    uint32_t sdesc_index1 = *(const uint32_t *)(data + 4);
    uint32_t tk2 = *(const uint32_t *)(data + 8);
    uint32_t sdesc_index2 = *(const uint32_t *)(data + 12);

    // Call the function-under-test
    gf_isom_is_same_sample_description(f1, tk1, sdesc_index1, f2, tk2, sdesc_index2);

    // Clean up
    gf_isom_close(f1);
    gf_isom_close(f2);

    return 0;
}