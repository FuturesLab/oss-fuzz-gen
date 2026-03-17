#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("sample.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) return 0;

    u32 trackNumber = 1; // Assuming track number 1 for testing
    u32 StreamDescriptionIndex = 1; // Assuming stream description index 1 for testing

    GF_MasteringDisplayColourVolumeInfo mdcv;
    GF_ContentLightLevelInfo clli;

    // Initialize mdcv with some test values
    mdcv.display_primaries[0].x = 34000;
    mdcv.display_primaries[0].y = 16000;
    mdcv.display_primaries[1].x = 13250;
    mdcv.display_primaries[1].y = 34500;
    mdcv.display_primaries[2].x = 7500;
    mdcv.display_primaries[2].y = 3000;
    mdcv.white_point_x = 15635; // Updated member name
    mdcv.white_point_y = 16450; // Updated member name
    mdcv.max_display_mastering_luminance = 1000;
    mdcv.min_display_mastering_luminance = 1;

    // Initialize clli with some test values
    clli.max_content_light_level = 1000;
    clli.max_pic_average_light_level = 400;

    // Call the function-under-test
    gf_isom_set_high_dynamic_range_info(movie, trackNumber, StreamDescriptionIndex, &mdcv, &clli);

    // Close the movie file
    gf_isom_close(movie);

    return 0;
}