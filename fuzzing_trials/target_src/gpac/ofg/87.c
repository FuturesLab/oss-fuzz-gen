#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/internal/isomedia_dev.h> // Include the header with the full definition of GF_ISOFile

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure we have enough data for two u32 values and two GF_ISOFile pointers
    if (size < sizeof(u32) * 4) {
        return 0;
    }

    // Extract u32 values from the data
    u32 tk1 = *((u32*)data);
    u32 sdesc_index1 = *((u32*)(data + sizeof(u32)));
    u32 tk2 = *((u32*)(data + sizeof(u32) * 2));
    u32 sdesc_index2 = *((u32*)(data + sizeof(u32) * 3));

    // Create dummy GF_ISOFile objects
    GF_ISOFile f1, f2;

    // Call the function under test
    gf_isom_is_same_sample_description(&f1, tk1, sdesc_index1, &f2, tk2, sdesc_index2);

    return 0;
}