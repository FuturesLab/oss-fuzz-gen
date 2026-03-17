#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our parameters
    if (size < sizeof(u32) * 4 + sizeof(s32)) {
        return 0;
    }

    // Initialize variables for the function parameters
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    u32 track = *((u32 *)data);
    u32 sampleNumber = *((u32 *)(data + sizeof(u32)));
    s32 refID = *((s32 *)(data + 2 * sizeof(u32)));
    u32 nb_refs = *((u32 *)(data + 2 * sizeof(u32) + sizeof(s32)));

    // Ensure nb_refs does not exceed the available data size
    if (nb_refs * sizeof(s32) > size - (3 * sizeof(u32) + sizeof(s32))) {
        nb_refs = (size - (3 * sizeof(u32) + sizeof(s32))) / sizeof(s32);
    }

    s32 *refs = (s32 *)(data + 3 * sizeof(u32) + sizeof(s32));

    // Call the function-under-test
    gf_isom_set_sample_references(file, track, sampleNumber, refID, nb_refs, refs);

    // Clean up
    gf_isom_close(file);

    return 0;
}