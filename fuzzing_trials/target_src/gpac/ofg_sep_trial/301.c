#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    const char *URLname = "http://example.com";
    const char *URNname = "urn:example";
    u32 outDescriptionIndex = 0;
    u8 *dsi = NULL;
    u32 dsi_len = size;

    // Allocate memory for dsi if size is greater than 0
    if (size > 0) {
        dsi = (u8 *)malloc(size);
        if (dsi == NULL) {
            gf_isom_close(the_file);
            return 0;
        }
        memcpy(dsi, data, size);
    }

    // Call the function-under-test
    gf_isom_new_mj2k_description(the_file, trackNumber, URLname, URNname, &outDescriptionIndex, dsi, dsi_len);

    // Clean up
    if (dsi != NULL) {
        free(dsi);
    }
    gf_isom_close(the_file);

    return 0;
}