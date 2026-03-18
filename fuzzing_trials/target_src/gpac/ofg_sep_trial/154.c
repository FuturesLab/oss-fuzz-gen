#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Initialize GF_ISOFile
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Ensure the input size is sufficient to extract a track number
    if (size < sizeof(uint32_t)) {
        gf_isom_close(file);
        return 0;
    }

    // Extract a track number from the input data
    uint32_t track = *(const uint32_t *)data;

    // Call the function-under-test
    gf_isom_find_od_id_for_track(file, track);

    // Clean up
    gf_isom_close(file);

    return 0;
}