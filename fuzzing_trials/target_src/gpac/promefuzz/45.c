// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_vvc_set_inband_config at avc_ext.c:2427:8 in isomedia.h
// gf_isom_set_sample_av1_switch_frame_group at isom_write.c:7740:8 in isomedia.h
// gf_isom_get_sample_rap_roll_info at isom_read.c:5119:8 in isomedia.h
// gf_isom_fragment_set_sample_rap_group at isom_write.c:7720:8 in isomedia.h
// gf_isom_fragment_set_sample_av1_switch_frame_group at isom_write.c:7745:8 in isomedia.h
// gf_isom_set_sample_rap_group at isom_write.c:7715:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
}

static void cleanup_iso_file(GF_ISOFile *iso_file) {
    if (iso_file) {
        gf_isom_close(iso_file);
    }
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Dummy file creation
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Randomly initialize parameters for each function
    u32 trackNumber = (Size > 4) ? *(u32 *)Data : 1;
    u32 sampleDescriptionIndex = (Size > 8) ? *(u32 *)(Data + 4) : 1;
    u32 sampleNumber = (Size > 12) ? *(u32 *)(Data + 8) : 1;
    Bool is_rap = (Size > 13) ? (Data[12] % 2) : 0;
    u32 num_leading_samples = (Size > 17) ? *(u32 *)(Data + 13) : 0;
    Bool keep_xps = (Size > 18) ? (Data[17] % 2) : 0;
    Bool is_switch_Frame = (Size > 19) ? (Data[18] % 2) : 0;

    // Call gf_isom_vvc_set_inband_config
    gf_isom_vvc_set_inband_config(iso_file, trackNumber, sampleDescriptionIndex, keep_xps);

    // Call gf_isom_set_sample_av1_switch_frame_group
    gf_isom_set_sample_av1_switch_frame_group(iso_file, trackNumber, sampleNumber, is_switch_Frame);

    // Prepare variables for gf_isom_get_sample_rap_roll_info
    Bool is_rap_out;
    GF_ISOSampleRollType roll_type;
    s32 roll_distance;

    // Call gf_isom_get_sample_rap_roll_info
    gf_isom_get_sample_rap_roll_info(iso_file, trackNumber, sampleNumber, &is_rap_out, &roll_type, &roll_distance);

    // Call gf_isom_fragment_set_sample_rap_group
    gf_isom_fragment_set_sample_rap_group(iso_file, trackNumber, sampleNumber, is_rap, num_leading_samples);

    // Call gf_isom_fragment_set_sample_av1_switch_frame_group
    gf_isom_fragment_set_sample_av1_switch_frame_group(iso_file, trackNumber, sampleNumber, is_switch_Frame);

    // Call gf_isom_set_sample_rap_group
    gf_isom_set_sample_rap_group(iso_file, trackNumber, sampleNumber, is_rap, num_leading_samples);

    // Cleanup
    cleanup_iso_file(iso_file);

    return 0;
}