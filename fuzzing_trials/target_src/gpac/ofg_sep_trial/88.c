#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1; // Use a non-zero track number
    GF_3GPConfig cfg;
    memset(&cfg, 0, sizeof(GF_3GPConfig)); // Initialize the config structure

    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;

    // Use the input data to feed the function under test
    if (size > 0) {
        URLname = (const char *)data; // Use input data as URLname if size permits
    }
    if (size > strlen(URLname) + 1) {
        URNname = (const char *)(data + strlen(URLname) + 1); // Use remaining data as URNname
    }

    // Call the function-under-test
    gf_isom_3gp_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}