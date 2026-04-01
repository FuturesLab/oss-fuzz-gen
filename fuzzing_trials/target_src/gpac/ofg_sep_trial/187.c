#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    if (size < sizeof(GF_HEVCConfig) + 2 * sizeof(char) + sizeof(u32)) {
        return 0;
    }

    // Initialize the_file
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Initialize trackNumber
    u32 trackNumber = 1;

    // Initialize cfg
    GF_HEVCConfig *cfg = (GF_HEVCConfig *)malloc(sizeof(GF_HEVCConfig));
    if (!cfg) {
        gf_isom_close(the_file);
        return 0;
    }
    memset(cfg, 0, sizeof(GF_HEVCConfig));

    // Initialize URLname and URNname
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example:config";

    // Initialize outDescriptionIndex
    u32 *outDescriptionIndex = (u32 *)malloc(sizeof(u32));
    if (!outDescriptionIndex) {
        free(cfg);
        gf_isom_close(the_file);
        return 0;
    }
    *outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_hevc_config_new(the_file, trackNumber, cfg, URLname, URNname, outDescriptionIndex);

    // Cleanup
    free(cfg);
    free(outDescriptionIndex);
    gf_isom_close(the_file);

    return 0;
}