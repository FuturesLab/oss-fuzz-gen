#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* create_dummy_iso_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    GF_ISOFile *iso_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return iso_file;
}

int LLVMFuzzerTestOneInput_295(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    GF_ISOFile *iso_file = create_dummy_iso_file(Data, Size);
    if (!iso_file) {
        return 0;
    }

    u32 trackNumber = Data[0];
    s64 mediaOffset = 0;
    u32 moof_index = Data[1];
    GF_ISOTrackID trackID = Data[2];
    u32 MediaType = Data[3];
    u32 TimeScale = 1000;

    // Fuzz gf_isom_get_edit_list_type
    Bool isComplex = gf_isom_get_edit_list_type(iso_file, trackNumber, &mediaOffset);

    // Fuzz gf_isom_get_track_count
    u32 trackCount = gf_isom_get_track_count(iso_file);

    // Fuzz gf_isom_segment_get_track_fragment_count

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_segment_get_track_fragment_count with gf_isom_get_constant_sample_size
    u32 fragmentCount = gf_isom_get_constant_sample_size(iso_file, moof_index);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_get_media_type
    u32 mediaType = gf_isom_get_media_type(iso_file, trackNumber);

    // Fuzz gf_isom_get_cts_to_dts_shift
    s64 ctsToDtsShift = gf_isom_get_cts_to_dts_shift(iso_file, trackNumber);

    // Fuzz gf_isom_new_track
    u32 newTrackNumber = gf_isom_new_track(iso_file, trackID, MediaType, TimeScale);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_new_track to gf_isom_get_payt_info
    Bool ret_gf_isom_is_smooth_streaming_moov_agkkv = gf_isom_is_smooth_streaming_moov(iso_file);

    const char * ret_gf_isom_get_payt_info_jfxnd = gf_isom_get_payt_info(iso_file, trackCount, mediaType, &newTrackNumber);
    if (ret_gf_isom_get_payt_info_jfxnd == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(iso_file);
    return 0;
}