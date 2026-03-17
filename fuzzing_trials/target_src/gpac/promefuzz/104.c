// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_get_track_matrix at isom_read.c:4107:8 in isomedia.h
// gf_isom_set_track_reference at isom_write.c:4967:8 in isomedia.h
// gf_isom_get_original_format_type at drm_sample.c:649:8 in isomedia.h
// gf_isom_sdp_clean_track at hint_track.c:790:8 in isomedia.h
// gf_isom_get_audio_info at isom_read.c:3880:8 in isomedia.h
// gf_isom_rtp_set_time_offset at hint_track.c:259:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static GF_ISOFile* create_dummy_isofile() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Create a dummy ISO file structure
    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    // Variables for API function calls
    u32 trackNumber = 1;
    u32 matrix[9] = {0};
    u32 referenceType = 0x72656631; // 'ref1'
    GF_ISOTrackID ReferencedTrackID = 2;
    u32 sampleDescriptionIndex = 1;
    u32 outOriginalFormat = 0;
    u32 SampleRate = 0, Channels = 0, bitsPerSample = 0;
    u32 HintDescriptionIndex = 1;
    u32 TimeOffset = 0;

    // Call gf_isom_get_track_matrix
    gf_isom_get_track_matrix(isom_file, trackNumber, matrix);

    // Call gf_isom_set_track_reference
    gf_isom_set_track_reference(isom_file, trackNumber, referenceType, ReferencedTrackID);

    // Call gf_isom_get_original_format_type
    gf_isom_get_original_format_type(isom_file, trackNumber, sampleDescriptionIndex, &outOriginalFormat);

    // Call gf_isom_sdp_clean_track
    gf_isom_sdp_clean_track(isom_file, trackNumber);

    // Call gf_isom_get_audio_info
    gf_isom_get_audio_info(isom_file, trackNumber, sampleDescriptionIndex, &SampleRate, &Channels, &bitsPerSample);

    // Call gf_isom_rtp_set_time_offset
    gf_isom_rtp_set_time_offset(isom_file, trackNumber, HintDescriptionIndex, TimeOffset);

    // Cleanup
    gf_isom_close(isom_file);
    return 0;
}