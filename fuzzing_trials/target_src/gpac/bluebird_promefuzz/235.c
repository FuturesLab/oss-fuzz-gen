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
    
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return isom_file;
}

int LLVMFuzzerTestOneInput_235(const uint8_t *Data, size_t Size) {
    if (Size < 4) {
        return 0;
    }

    GF_ISOFile *isom_file = create_dummy_iso_file(Data, Size);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = Data[0];
    u32 sampleNumber = Data[1];
    u32 groupIndex = Data[2];
    u32 referenceType = Data[3];

    // Test gf_isom_get_sample_duration
    u32 duration = gf_isom_get_sample_duration(isom_file, trackNumber, sampleNumber);

    // Test gf_isom_has_time_offset
    u32 has_time_offset = gf_isom_has_time_offset(isom_file, trackNumber);

    // Test gf_isom_get_timescale
    u32 timescale = gf_isom_get_timescale(isom_file);

    // Test gf_isom_get_track_switch_parameter
    u32 switchGroupID;
    u32 criteriaListSize;
    const u32 *criteriaList = gf_isom_get_track_switch_parameter(isom_file, trackNumber, groupIndex, &switchGroupID, &criteriaListSize);

    // Test gf_isom_is_track_referenced

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_is_track_referenced with gf_isom_get_sample_size
    u32 referencedTrack = gf_isom_get_sample_size(isom_file, trackNumber, referenceType);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Test gf_isom_segment_get_fragment_count
    u32 fragmentCount = gf_isom_segment_get_fragment_count(isom_file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_set_sample_av1_switch_frame_group
    u32 ret_gf_isom_get_next_alternate_group_id_pheeg = gf_isom_get_next_alternate_group_id(NULL);
    u32 ret_gf_isom_get_track_count_mxmhd = gf_isom_get_track_count(NULL);
    Bool ret_gf_isom_is_inplace_rewrite_lwrfq = gf_isom_is_inplace_rewrite(NULL);

    GF_Err ret_gf_isom_set_sample_av1_switch_frame_group_rqofu = gf_isom_set_sample_av1_switch_frame_group(isom_file, ret_gf_isom_get_next_alternate_group_id_pheeg, ret_gf_isom_get_track_count_mxmhd, ret_gf_isom_is_inplace_rewrite_lwrfq);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(isom_file);
    return 0;
}