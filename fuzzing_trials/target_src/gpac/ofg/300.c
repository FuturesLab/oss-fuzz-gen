#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1;  // Example track number
    const char *URLname = "http://example.com";  // Example URL
    const char *URNname = "urn:example";  // Example URN
    u32 outDescriptionIndex = 0;
    u8 *dsi = NULL;
    u32 dsi_len = 0;

    // Ensure dsi is not NULL
    if (size > 0) {
        dsi = (u8 *)malloc(size);
        if (dsi == NULL) {
            gf_isom_close(the_file);
            return 0;
        }
        memcpy(dsi, data, size);
        dsi_len = size;
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