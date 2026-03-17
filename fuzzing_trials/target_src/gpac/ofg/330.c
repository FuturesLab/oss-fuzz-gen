#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_330(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Exit if the movie cannot be opened
    }

    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index

    GF_DOVIDecoderConfigurationRecord dvcc;
    // Initialize the dvcc structure with some example values
    dvcc.dv_version_major = 1;
    dvcc.dv_version_minor = 0;
    dvcc.dv_profile = 5; // Example Dolby Vision profile
    dvcc.dv_level = 3; // Example Dolby Vision level
    dvcc.rpu_present_flag = 1;
    dvcc.el_present_flag = 0;
    dvcc.bl_present_flag = 1;
    dvcc.dv_bl_signal_compatibility_id = 0;
    dvcc.dv_md_compression = 0;
    dvcc.force_dv = 0;

    // Call the function under test
    gf_isom_set_dolby_vision_profile(movie, trackNumber, StreamDescriptionIndex, &dvcc);

    // Clean up
    gf_isom_close(movie);

    return 0;
}