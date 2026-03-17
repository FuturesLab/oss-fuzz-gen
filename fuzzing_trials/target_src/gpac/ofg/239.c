#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for the required parameters
    if (size < sizeof(uint32_t) * 2) {
        return 0;
    }

    // Initialize parameters for the function-under-test
    GF_ISOFile *isom_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL); // Open a dummy file
    if (!isom_file) {
        return 0;
    }

    uint32_t trackNumber = *((uint32_t *)data);
    uint32_t sampleDescriptionIndex = *((uint32_t *)(data + sizeof(uint32_t)));
    GF_OpusConfig opcfg;

    // Call the function-under-test
    gf_isom_opus_config_get_desc(isom_file, trackNumber, sampleDescriptionIndex, &opcfg);

    // Clean up
    gf_isom_close(isom_file);

    return 0;
}