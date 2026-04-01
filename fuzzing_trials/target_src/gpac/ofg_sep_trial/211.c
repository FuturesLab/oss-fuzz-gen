#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Check if there is enough data for the known components
    if (size < sizeof(GF_AVCConfig) + 2 * sizeof(char) + sizeof(u32)) {
        return 0; // Not enough data to fill all parameters
    }

    // Initialize GF_ISOFile
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0; // Failed to open ISO file
    }

    // Extract trackNumber from data
    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    // Initialize GF_AVCConfig
    GF_AVCConfig *cfg = (GF_AVCConfig *)malloc(sizeof(GF_AVCConfig));
    if (!cfg) {
        gf_isom_close(the_file);
        return 0;
    }
    memset(cfg, 0, sizeof(GF_AVCConfig));

    // Extract URLname and URNname from data
    const char *URLname = (const char *)data;
    data += sizeof(char);
    size -= sizeof(char);

    const char *URNname = (const char *)data;
    data += sizeof(char);
    size -= sizeof(char);

    // Initialize outDescriptionIndex
    u32 *outDescriptionIndex = (u32 *)malloc(sizeof(u32));
    if (!outDescriptionIndex) {
        free(cfg);
        gf_isom_close(the_file);
        return 0;
    }
    *outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_svc_config_new(the_file, trackNumber, cfg, URLname, URNname, outDescriptionIndex);

    // Clean up
    free(cfg);
    free(outDescriptionIndex);
    gf_isom_close(the_file);

    return 0;
}