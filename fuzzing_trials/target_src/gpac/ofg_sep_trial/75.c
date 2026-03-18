#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    u32 track;
    Bool use_negative_offsets;

    // Initialize the GF_ISOFile structure
    file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    // Ensure size is sufficient to extract track and use_negative_offsets
    if (size < sizeof(u32) + sizeof(Bool)) {
        gf_isom_close(file);
        return 0;
    }

    // Extract track and use_negative_offsets from the data
    track = *((u32 *)data);
    use_negative_offsets = *((Bool *)(data + sizeof(u32)));

    // Call the function-under-test
    gf_isom_set_composition_offset_mode(file, track, use_negative_offsets);

    // Clean up
    gf_isom_close(file);

    return 0;
}