#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) return 0;

    u32 trackNumber = 1; // Example track number
    GF_HEVCConfig cfg;
    memset(&cfg, 0, sizeof(GF_HEVCConfig)); // Initialize the config structure

    // Ensure the URLname and URNname are not NULL
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_hevc_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}