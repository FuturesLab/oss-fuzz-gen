#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the necessary headers for GPAC library
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }
    
    u32 trackNumber = 1; // Example track number
    GF_AC3Config cfg; // Example AC3 configuration
    memset(&cfg, 0, sizeof(GF_AC3Config)); // Initialize the config structure

    // Use a part of the data as URLname and URNname
    const char *URLname = (const char *)data;
    const char *URNname = (const char *)(data + size / 2);

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_ac3_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}