#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_314(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to extract meaningful values
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize GF_ISOFile and GF_AVCConfig structures
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    GF_AVCConfig *cfg = gf_odf_avc_cfg_new();
    if (!cfg) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract trackNumber and DescriptionIndex from data
    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t DescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));

    // Call the function under test
    gf_isom_avc_config_update(the_file, trackNumber, DescriptionIndex, cfg);

    // Clean up
    gf_odf_avc_cfg_del(cfg);
    gf_isom_close(the_file);

    return 0;
}