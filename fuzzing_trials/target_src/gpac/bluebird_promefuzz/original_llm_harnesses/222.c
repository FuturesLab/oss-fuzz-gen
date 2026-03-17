// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_set_brand_info at isom_write.c:3520:8 in isomedia.h
// gf_isom_get_bitrate at isom_read.c:5967:8 in isomedia.h
// gf_isom_setup_hint_track at hint_track.c:90:8 in isomedia.h
// gf_isom_begin_hint_sample at hint_track.c:324:8 in isomedia.h
// gf_isom_set_audio_info at isom_write.c:2373:8 in isomedia.h
// gf_isom_set_track_reference at isom_write.c:4967:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    return gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size) {
    if (Size < 38) return 0; // Ensure enough data for fuzzing

    GF_ISOFile *isom_file = create_dummy_iso_file();
    if (!isom_file) return 0;

    u32 major_brand = *((u32 *)Data);
    u32 minor_version = *((u32 *)(Data + 4));
    u32 track_number = *((u32 *)(Data + 8));
    u32 sample_description_index = *((u32 *)(Data + 12));
    u32 hint_type = *((u32 *)(Data + 16));

    // Fuzz gf_isom_set_brand_info
    gf_isom_set_brand_info(isom_file, major_brand, minor_version);

    // Fuzz gf_isom_get_bitrate
    u32 average_bitrate, max_bitrate, decode_buffer_size;
    gf_isom_get_bitrate(isom_file, track_number, sample_description_index, &average_bitrate, &max_bitrate, &decode_buffer_size);

    // Fuzz gf_isom_setup_hint_track
    gf_isom_setup_hint_track(isom_file, track_number, (GF_ISOHintFormat)hint_type);

    // Fuzz gf_isom_begin_hint_sample
    gf_isom_begin_hint_sample(isom_file, track_number, sample_description_index, minor_version);

    // Fuzz gf_isom_set_audio_info
    u32 sample_rate = *((u32 *)(Data + 20));
    u32 nb_channels = *((u32 *)(Data + 24));
    u8 bits_per_sample = *(Data + 28);
    GF_AudioSampleEntryImportMode asemode = *(Data + 29);
    gf_isom_set_audio_info(isom_file, track_number, sample_description_index, sample_rate, nb_channels, bits_per_sample, asemode);

    // Fuzz gf_isom_set_track_reference
    u32 reference_type = *((u32 *)(Data + 30));
    GF_ISOTrackID referenced_track_id = *((u32 *)(Data + 34));
    gf_isom_set_track_reference(isom_file, track_number, reference_type, referenced_track_id);

    cleanup_iso_file(isom_file);
    return 0;
}