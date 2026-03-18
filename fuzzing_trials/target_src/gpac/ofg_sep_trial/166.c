#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Initialize the parameters for gf_isom_opus_config_new
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming a valid track number
    GF_OpusConfig cfg;
    memset(&cfg, 0, sizeof(GF_OpusConfig)); // Initialize the config structure

    // Allocate memory for URLname and URNname and ensure they are null-terminated
    char URLname[256];
    char URNname[256];
    if (size < 512) {
        memset(URLname, 0, sizeof(URLname));
        memset(URNname, 0, sizeof(URNname));
        memcpy(URLname, data, size < 256 ? size : 255);
        memcpy(URNname, data + (size < 256 ? 0 : 256), size < 256 ? 0 : size - 256);
    } else {
        memcpy(URLname, data, 255);
        memcpy(URNname, data + 256, 255);
        URLname[255] = '\0';
        URNname[255] = '\0';
    }

    u32 outDescriptionIndex = 0;

    // Call the function-under-test
    gf_isom_opus_config_new(the_file, trackNumber, &cfg, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}