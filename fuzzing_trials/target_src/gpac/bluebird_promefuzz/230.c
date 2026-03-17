#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming GF_ISOFile is created through a specific API, like an open function
    GF_ISOFile* iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return iso_file;
}

static void cleanup_iso_file(GF_ISOFile* iso_file) {
    if (!iso_file) return;
    gf_isom_close(iso_file);
}

int LLVMFuzzerTestOneInput_230(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile* iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzzing gf_isom_add_subsample
    if (Size >= 16) {
        u32 trackNumber = Data[0];
        u32 sampleNumber = Data[1];
        u32 flags = Data[2];
        u32 subSampleSize = Data[3];
        u8 priority = Data[4];
        u32 reserved = Data[5];
        Bool discardable = Data[6] % 2;
        gf_isom_add_subsample(iso_file, trackNumber, sampleNumber, flags, subSampleSize, priority, reserved, discardable);
    }

    // Fuzzing gf_isom_add_sample_group_info
    if (Size >= 20) {
        u32 trackNumber = Data[7];
        u32 grouping_type = Data[8];
        void *data = (void*)&Data[9];
        u32 data_size = Data[10];
        Bool is_default = Data[11] % 2;
        u32 sampleGroupDescriptionIndex;
        gf_isom_add_sample_group_info(iso_file, trackNumber, grouping_type, data, data_size, is_default, &sampleGroupDescriptionIndex);
    }

    // Fuzzing gf_isom_set_track_enabled
    if (Size >= 22) {
        u32 trackNumber = Data[12];
        Bool enableTrack = Data[13] % 2;
        gf_isom_set_track_enabled(iso_file, trackNumber, enableTrack);
    }

    // Fuzzing gf_isom_fragment_set_sample_rap_group
    if (Size >= 26) {
        GF_ISOTrackID trackID = Data[14];
        u32 sample_number_in_frag = Data[15];
        Bool is_rap = Data[16] % 2;
        u32 num_leading_samples = Data[17];
        gf_isom_fragment_set_sample_rap_group(iso_file, trackID, sample_number_in_frag, is_rap, num_leading_samples);
    }

    // Fuzzing gf_isom_hevc_set_tile_config
    if (Size >= 30) {
        u32 trackNumber = Data[18];
        u32 sampleDescriptionIndex = Data[19];
        GF_HEVCConfig *cfg = NULL;  // Assuming a NULL configuration for simplicity
        Bool is_base_track = Data[20] % 2;
        gf_isom_hevc_set_tile_config(iso_file, trackNumber, sampleDescriptionIndex, cfg, is_base_track);
    }

    // Fuzzing gf_isom_reset_track_switch_parameter
    if (Size >= 32) {
        u32 trackNumber = Data[21];
        Bool reset_all_group = Data[22] % 2;
        gf_isom_reset_track_switch_parameter(iso_file, trackNumber, reset_all_group);
    }

    cleanup_iso_file(iso_file);
    return 0;
}