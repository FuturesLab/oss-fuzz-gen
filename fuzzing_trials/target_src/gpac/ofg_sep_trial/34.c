#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h" // Include the header file for GPAC library

extern int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure OD_ID is within a valid range, e.g., 0 to UINT32_MAX
    u32 OD_ID = size > 0 ? (u32)data[0] : 1; // Use the first byte of data or a default value

    // Call the function-under-test
    gf_isom_set_root_od_id(movie, OD_ID);

    // Clean up
    gf_isom_close(movie);

    return 0;
}