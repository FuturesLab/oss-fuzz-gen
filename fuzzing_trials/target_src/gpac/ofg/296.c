#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1;
    u32 sampleDescriptionIndex = 1;

    GF_ISOM_Y3D_Info info;
    info.stereo_type = 0;
    info.projection_type = 0;
    info.meta_data = NULL;
    info.pose_present = 0;
    info.yaw = 0;
    info.pitch = 0;
    info.roll = 0;
    info.layout = 0;
    info.padding = 0;
    info.top = 0;
    info.bottom = 0;
    info.left = 0;
    info.right = 0;

    if (size >= sizeof(GF_ISOM_Y3D_Info)) {
        // Copy data to info if size is sufficient
        memcpy(&info, data, sizeof(GF_ISOM_Y3D_Info));
    }

    gf_isom_set_y3d_info(movie, trackNumber, sampleDescriptionIndex, &info);

    gf_isom_close(movie);

    return 0;
}