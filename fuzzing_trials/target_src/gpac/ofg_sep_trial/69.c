#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    u32 track = 0;

    // Create a temporary ISO file in memory
    // Provide a temporary directory for the third argument
    file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE | GF_ISOM_OPEN_READ, "/tmp");
    if (file == NULL) {
        return 0;
    }

    // Use the remaining data to set the track number
    if (size >= sizeof(u32)) {
        memcpy(&track, data, sizeof(u32));
    }

    // Call the function under test
    gf_isom_update_edit_list_duration(file, track);

    // Close the ISO file
    gf_isom_close(file);

    return 0;
}