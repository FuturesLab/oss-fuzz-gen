#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1;  // Arbitrary non-zero track number
    char URLname[256];
    char URNname[256];
    u32 format = 1;  // Arbitrary format value
    u32 peak_rate = 1000;  // Arbitrary peak rate
    u32 outDescriptionIndex = 0;

    // Ensure URLname and URNname are null-terminated strings
    size_t url_len = size < 255 ? size : 255;
    memcpy(URLname, data, url_len);
    URLname[url_len] = '\0';

    size_t urn_len = size < 255 ? size : 255;
    memcpy(URNname, data, urn_len);
    URNname[urn_len] = '\0';

    // Call the function-under-test
    gf_isom_truehd_config_new(the_file, trackNumber, URLname, URNname, format, peak_rate, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}