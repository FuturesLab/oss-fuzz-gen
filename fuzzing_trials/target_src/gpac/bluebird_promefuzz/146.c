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

static GF_ISOFile* create_dummy_isofile() {
    return NULL; // Return NULL as we cannot instantiate an incomplete type
}

static GF_ISOSample* create_dummy_sample() {
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (!sample) {
        return NULL;
    }
    memset(sample, 0, sizeof(GF_ISOSample));
    return sample;
}

int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    GF_ISOFile *isom_file = create_dummy_isofile();
    u32 trackNumber = Data[0] % 256;
    GF_ISONaluExtractMode nalu_extract_mode = Data[0] % 3;

    gf_isom_set_nalu_extract_mode(isom_file, trackNumber, nalu_extract_mode);

    u32 sampleDescriptionIndex = Data[0] % 256;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_nalu_extract_mode to gf_isom_flac_config_get
    u32 ret_gf_isom_segment_get_fragment_count_kygjo = gf_isom_segment_get_fragment_count(isom_file);
    u32 ret_gf_isom_segment_get_fragment_count_wrieh = gf_isom_segment_get_fragment_count(NULL);
    u32 ret_gf_isom_get_track_count_uckdc = gf_isom_get_track_count(isom_file);
    u8 *qxtxfhhz;
    memset(&qxtxfhhz, 0, sizeof(qxtxfhhz));

    GF_Err ret_gf_isom_flac_config_get_ewnyu = gf_isom_flac_config_get(isom_file, ret_gf_isom_segment_get_fragment_count_kygjo, ret_gf_isom_segment_get_fragment_count_wrieh, &qxtxfhhz, &ret_gf_isom_get_track_count_uckdc);

    // End mutation: Producer.APPEND_MUTATOR

    GF_ISOSample *sample = create_dummy_sample();
    u64 dataOffset = (Size > 8) ? *((u64*)(Data + 1)) : 0;

    gf_isom_add_sample_reference(isom_file, trackNumber, sampleDescriptionIndex, sample, dataOffset);

    Bool root_meta = (Bool)(Data[0] % 2);
    u32 item_id = Data[0] % 256;
    GF_ImageItemProperties out_image_props;
    GF_List *unmapped_props = NULL;

    gf_isom_get_meta_image_props(isom_file, root_meta, trackNumber, item_id, &out_image_props, unmapped_props);

    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        gf_isom_dump_supported_box(Data[0] % 256, dummy_file);
        fclose(dummy_file);
    }

    dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        GF_TextDumpType dump_type = Data[0] % 3;
        gf_isom_text_dump(isom_file, trackNumber, dummy_file, dump_type);
        fclose(dummy_file);
    }

    u64 desiredTime = (Size > 8) ? *((u64*)(Data + 1)) : 0;
    u32 sampleDescriptionIndexOut;
    GF_ISOSearchMode SearchMode = Data[0] % 3;
    GF_ISOSample *sampleOut = NULL;
    u32 sample_number;
    u64 data_offset;

    gf_isom_get_sample_for_media_time(isom_file, trackNumber, desiredTime, &sampleDescriptionIndexOut, SearchMode, &sampleOut, &sample_number, &data_offset);

    free(sample);
    return 0;
}