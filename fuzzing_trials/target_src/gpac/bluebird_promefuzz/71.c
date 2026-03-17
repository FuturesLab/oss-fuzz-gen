#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const uint8_t *Data, size_t Size) {
    // Open the dummy file to simulate the ISO file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }

    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the file using the gpac API
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) {
        return 0;
    } // Ensure we have enough data

    GF_ISOFile *isom_file = initialize_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 moof_index = *(u32 *)Data;
    u32 traf_index = *((u32 *)Data + 1);
    u32 trackNumber = *((u32 *)Data + 2);
    u64 decode_time = 0;

    // Fuzz gf_isom_segment_get_track_fragment_decode_time
    u32 track_id = gf_isom_segment_get_track_fragment_decode_time(isom_file, moof_index, traf_index, &decode_time);

    // Fuzz gf_isom_get_sample_description_index
    u64 for_time = (Size > sizeof(u32) * 3) ? *((u64 *)(Data + sizeof(u32) * 3)) : 0;
    u32 sample_desc_index = gf_isom_get_sample_description_index(isom_file, trackNumber, for_time);

    // Fuzz gf_isom_get_track_duration
    u64 track_duration = gf_isom_get_track_duration(isom_file, trackNumber);

    // Fuzz gf_isom_get_sample_dts
    u32 sampleNumber = (Size > sizeof(u32) * 4) ? *((u32 *)(Data + sizeof(u32) * 4)) : 1;
    u64 sample_dts = gf_isom_get_sample_dts(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_get_sample_from_dts
    u64 dts = (Size > sizeof(u32) * 5) ? *((u64 *)(Data + sizeof(u32) * 5)) : 0;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_sample_dts to gf_isom_apple_enum_tag
    u32 ret_gf_isom_segment_get_fragment_count_dtjbe = gf_isom_segment_get_fragment_count(isom_file);
    u32 ret_gf_isom_probe_file_optba = gf_isom_probe_file((const char *)"r");
    u32 ret_gf_isom_get_copyright_count_deytl = gf_isom_get_copyright_count(isom_file);
    u32 ret_gf_isom_text_sample_size_yevzn = gf_isom_text_sample_size(NULL);
    u32 ret_gf_isom_get_next_moof_number_nqkyc = gf_isom_get_next_moof_number(isom_file);
    const u8 *khsoxpfe;
    memset(&khsoxpfe, 0, sizeof(khsoxpfe));

    GF_Err ret_gf_isom_apple_enum_tag_zdqrj = gf_isom_apple_enum_tag(isom_file, ret_gf_isom_probe_file_optba, NULL, &khsoxpfe, &ret_gf_isom_get_copyright_count_deytl, &sample_dts, &ret_gf_isom_text_sample_size_yevzn, &ret_gf_isom_get_next_moof_number_nqkyc);

    // End mutation: Producer.APPEND_MUTATOR

    u32 sample_from_dts = gf_isom_get_sample_from_dts(isom_file, trackNumber, dts);

    // Fuzz gf_isom_get_media_data_size
    u64 media_data_size = gf_isom_get_media_data_size(isom_file, trackNumber);

    // Clean up
    cleanup_iso_file(isom_file);

    return 0;
}