#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("test.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming track number 1 for testing
    GF_AVCConfig cfg;
    memset(&cfg, 0, sizeof(GF_AVCConfig)); // Initialize config structure

    // Use a portion of the data as URLname and URNname
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";

    u32 outDescriptionIndex = 0;

    // Call the function under test
    gf_isom_svc_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}