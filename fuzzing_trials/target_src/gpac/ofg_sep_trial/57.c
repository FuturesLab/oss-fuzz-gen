#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    u32 colour_type = (size > 0) ? data[0] : 0;
    u16 colour_primaries = (size > 1) ? data[1] : 1;
    u16 transfer_characteristics = (size > 2) ? data[2] : 1;
    u16 matrix_coefficients = (size > 3) ? data[3] : 1;
    Bool full_range_flag = (size > 4) ? data[4] % 2 : 0;
    u8 *icc_data = (size > 5) ? (u8 *)&data[5] : NULL;
    u32 icc_size = (size > 5) ? size - 5 : 0;

    gf_isom_set_visual_color_info(movie, trackNumber, StreamDescriptionIndex, colour_type, colour_primaries, transfer_characteristics, matrix_coefficients, full_range_flag, icc_data, icc_size);

    gf_isom_close(movie);
    return 0;
}