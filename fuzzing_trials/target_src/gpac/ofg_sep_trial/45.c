#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract necessary values
    if (size < sizeof(u32) * 3) {
        return 0;
    }

    // Initialize the parameters for gf_isom_truehd_config_new
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    char URLname[256];
    snprintf(URLname, sizeof(URLname), "http://example.com/%u", trackNumber);

    char URNname[256];
    snprintf(URNname, sizeof(URNname), "urn:example:%u", trackNumber);

    u32 format = *((u32 *)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    u32 peak_rate = *((u32 *)data);

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_truehd_config_new(the_file, trackNumber, URLname, URNname, format, peak_rate, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}