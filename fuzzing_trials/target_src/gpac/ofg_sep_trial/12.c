#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming a valid track number
    GF_AV1Config cfg;
    cfg.marker = 1; // Initialize with some non-zero value
    cfg.version = 1; // Initialize with some non-zero value

    const char *URLname = "http://example.com";
    const char *URNname = "exampleURN";

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_av1_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}