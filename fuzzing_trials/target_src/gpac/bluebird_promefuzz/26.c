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

static void prepare_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) {
        return 0;
    }

    // Prepare the dummy file
    prepare_dummy_file(Data, Size);

    // Initialize variables for API functions
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *((u32 *)Data);
    u32 sampleNumber = *((u32 *)(Data + sizeof(u32)));
    u32 sampleDescriptionIndex = *((u32 *)(Data + 2 * sizeof(u32)));

    FILE *trace = fopen("./trace_output", "w");
    if (!trace) {
        gf_isom_close(isom_file);
        return 0;
    }

    // Fuzz gf_isom_dump_ismacryp_protection
    gf_isom_dump_ismacryp_protection(isom_file, trackNumber, trace);

    // Fuzz gf_isom_get_sample_references
    u32 refID, nb_refs;
    const u32 *refs;
    gf_isom_get_sample_references(isom_file, trackNumber, sampleNumber, &refID, &nb_refs, &refs);

    // Fuzz gf_isom_dump_ismacryp_sample
    gf_isom_dump_ismacryp_sample(isom_file, trackNumber, sampleNumber, trace);

    // Fuzz gf_isom_set_sample_cenc_default_group
    gf_isom_set_sample_cenc_default_group(isom_file, trackNumber, sampleNumber);

    // Fuzz gf_isom_update_bitrate
    u32 average_bitrate = *((u32 *)(Data + 3 * sizeof(u32)));
    u32 max_bitrate = *((u32 *)(Data + 4 * sizeof(u32)));
    u32 decode_buffer_size = *((u32 *)(Data + 5 * sizeof(u32)));
    gf_isom_update_bitrate(isom_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    // Fuzz gf_isom_dump_hint_sample
    gf_isom_dump_hint_sample(isom_file, trackNumber, sampleNumber, trace);

    // Cleanup
    fclose(trace);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_close to gf_isom_extract_meta_item_get_cenc_info
        u32 ret_gf_isom_segment_get_fragment_count_yloeo = gf_isom_segment_get_fragment_count(isom_file);
        u32 ret_gf_isom_probe_file_mjcqd = gf_isom_probe_file((const char *)"r");
        Bool ret_gf_isom_is_single_av_tadbe = gf_isom_is_single_av(isom_file);
        u32 ret_gf_isom_get_next_moof_number_yaopz = gf_isom_get_next_moof_number(NULL);
        u32 ret_gf_isom_probe_file_iibvj = gf_isom_probe_file((const char *)"w");
        u32 ret_gf_isom_get_next_moof_number_luokh = gf_isom_get_next_moof_number(isom_file);
        u32 ret_gf_isom_probe_file_yhpmr = gf_isom_probe_file((const char *)Data);
        u32 nzrmfjgs;
        memset(&nzrmfjgs, 0, sizeof(nzrmfjgs));
        const u8 *ofcoqupo;
        memset(&ofcoqupo, 0, sizeof(ofcoqupo));
        u8 *bxoemfxw;
        memset(&bxoemfxw, 0, sizeof(bxoemfxw));

        GF_Err ret_gf_isom_extract_meta_item_get_cenc_info_astsn = gf_isom_extract_meta_item_get_cenc_info(isom_file, 0, ret_gf_isom_segment_get_fragment_count_yloeo, ret_gf_isom_probe_file_mjcqd, &ret_gf_isom_is_single_av_tadbe, &ret_gf_isom_get_next_moof_number_yaopz, &nzrmfjgs, &ofcoqupo, &ret_gf_isom_probe_file_iibvj, &ret_gf_isom_get_next_moof_number_luokh, &bxoemfxw, &ret_gf_isom_probe_file_yhpmr, NULL);

        // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(isom_file);

    return 0;
}