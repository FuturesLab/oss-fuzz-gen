#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to extract parameters
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Extract track and ctts_shift from the data
    uint32_t track = *(uint32_t *)data;
    uint32_t ctts_shift = *(uint32_t *)(data + sizeof(uint32_t));

    // Initialize a GF_ISOFile object with the correct number of arguments
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_set_ctts_v1(file, track, ctts_shift);

    // Clean up
    gf_isom_close(file);

    return 0;
}