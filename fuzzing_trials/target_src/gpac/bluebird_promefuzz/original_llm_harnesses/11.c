// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_rewrite_track_dependencies at isom_write.c:5120:8 in isomedia.h
// gf_isom_get_track_switch_group_count at isom_read.c:4813:8 in isomedia.h
// gf_isom_get_audio_info at isom_read.c:3880:8 in isomedia.h
// gf_isom_remove_track at isom_write.c:2942:8 in isomedia.h
// gf_isom_truehd_config_get at sample_descs.c:416:8 in isomedia.h
// gf_isom_set_last_sample_duration_ex at isom_write.c:1431:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Create a dummy ISO file
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void destroy_dummy_iso_file(GF_ISOFile *isom_file) {
    // Clean up the dummy ISO file
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 dummyValue = *((u32 *)(Data + 2 * sizeof(u32)));

    // Prepare output variables
    u32 alternateGroupID = 0;
    u32 nb_groups = 0;
    u32 SampleRate = 0;
    u32 Channels = 0;
    u32 bitsPerSample = 0;
    u32 format_info = 0;
    u32 peak_data_rate = 0;

    // Test gf_isom_rewrite_track_dependencies
    gf_isom_rewrite_track_dependencies(isom_file, trackNumber);

    // Test gf_isom_get_track_switch_group_count
    gf_isom_get_track_switch_group_count(isom_file, trackNumber, &alternateGroupID, &nb_groups);

    // Test gf_isom_get_audio_info
    gf_isom_get_audio_info(isom_file, trackNumber, sampleDescriptionIndex, &SampleRate, &Channels, &bitsPerSample);

    // Test gf_isom_remove_track
    gf_isom_remove_track(isom_file, trackNumber);

    // Test gf_isom_truehd_config_get
    gf_isom_truehd_config_get(isom_file, trackNumber, sampleDescriptionIndex, &format_info, &peak_data_rate);

    // Test gf_isom_set_last_sample_duration_ex
    gf_isom_set_last_sample_duration_ex(isom_file, trackNumber, dummyValue, dummyValue);

    destroy_dummy_iso_file(isom_file);

    return 0;
}