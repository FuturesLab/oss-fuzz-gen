#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    if (size < 3 * sizeof(u32) + sizeof(u8*)) {
        return 0; // Not enough data to initialize all parameters
    }

    // Initialize parameters for gf_isom_text_get_encoded_tx3g
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!file) return 0;

    u32 track = *(u32 *)(data);
    u32 sidx = *(u32 *)(data + sizeof(u32));
    u32 sidx_offset = *(u32 *)(data + 2 * sizeof(u32));

    u8 *tx3g = NULL;
    u32 tx3g_size = 0;

    // Call the function-under-test
    GF_Err result = gf_isom_text_get_encoded_tx3g(file, track, sidx, sidx_offset, &tx3g, &tx3g_size);

    // Clean up
    if (tx3g) {
        free(tx3g);
    }
    gf_isom_close(file);

    return 0;
}