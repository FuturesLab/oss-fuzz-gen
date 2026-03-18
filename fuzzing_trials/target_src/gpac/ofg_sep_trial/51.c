#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0; // Return early if file opening fails
    }
    
    u32 trackNumber = 1; // Example track number
    u32 fps_num = 30; // Example frames per second numerator
    u32 fps_den = 1; // Example frames per second denominator
    s32 frames_per_counter_tick = 1; // Example frames per counter tick
    Bool is_drop = GF_FALSE; // Example boolean value
    Bool is_counter = GF_TRUE; // Example boolean value
    u32 outDescriptionIndex = 0; // Initialize output description index

    // Use input data to simulate different configurations
    if (size >= sizeof(u32)) {
        trackNumber = *((u32 *)data);
    }
    if (size >= 2 * sizeof(u32)) {
        fps_num = *((u32 *)(data + sizeof(u32)));
    }

    // Call the function-under-test
    gf_isom_tmcd_config_new(the_file, trackNumber, fps_num, fps_den, frames_per_counter_tick, is_drop, is_counter, &outDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);

    return 0;
}