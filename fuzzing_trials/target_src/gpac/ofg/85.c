#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary parameters
    if (size < sizeof(uint32_t) * 2 + sizeof(GF_HEVCConfig)) {
        return 0;
    }

    // Initialize the parameters
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        return 0;
    }

    uint32_t trackNumber = *(uint32_t *)(data);
    uint32_t DescriptionIndex = *(uint32_t *)(data + sizeof(uint32_t));
    GF_HEVCConfig *cfg = (GF_HEVCConfig *)(data + sizeof(uint32_t) * 2);

    // Call the function under test
    gf_isom_hevc_config_update(the_file, trackNumber, DescriptionIndex, cfg);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}