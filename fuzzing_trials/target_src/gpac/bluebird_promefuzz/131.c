#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* initialize_iso_file(const char *filename) {
    // Open the file in read/write mode, assuming a function for this exists.
    GF_ISOFile *isom_file = gf_isom_open(filename, GF_ISOM_OPEN_EDIT, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5) {
        return 0;
    }

    // Create a dummy file to simulate the ISO file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    GF_ISOFile *isom_file = initialize_iso_file("./dummy_file");
    if (!isom_file) {
        return 0;
    }

    u32 trackNumber = *(u32 *)Data;
    u32 ref_type = *((u32 *)Data + 1);
    u32 group_id = *((u32 *)Data + 2);
    u32 max_chunk_size = *((u32 *)Data + 3);
    u32 new_media_type = *((u32 *)Data + 4);

    // Fuzz gf_isom_remove_track_from_root_od
    gf_isom_remove_track_from_root_od(isom_file, trackNumber);

    // Fuzz gf_isom_remove_track_reference
    gf_isom_remove_track_reference(isom_file, trackNumber, ref_type);

    // Fuzz gf_isom_set_track_interleaving_group
    gf_isom_set_track_interleaving_group(isom_file, trackNumber, group_id);

    // Fuzz gf_isom_set_alternate_group_id
    gf_isom_set_alternate_group_id(isom_file, trackNumber, group_id);

    // Fuzz gf_isom_hint_max_chunk_size

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_hint_max_chunk_size with gf_isom_set_ctts_v1

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_alternate_group_id to gf_isom_clone_track
    u32 ret_gf_isom_get_copyright_count_bxjqu = gf_isom_get_copyright_count(isom_file);
    GF_Err ret_gf_isom_sdp_clean_ahvse = gf_isom_sdp_clean(isom_file);
    u32 ret_gf_isom_get_copyright_count_ssnmc = gf_isom_get_copyright_count(isom_file);

    GF_Err ret_gf_isom_clone_track_tvgpj = gf_isom_clone_track(isom_file, ret_gf_isom_get_copyright_count_bxjqu, isom_file, 0, &ret_gf_isom_get_copyright_count_ssnmc);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_set_ctts_v1(isom_file, trackNumber, max_chunk_size);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz gf_isom_set_media_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_ctts_v1 to gf_isom_hevc_set_inband_config
    u32 ret_gf_isom_get_timescale_uabxl = gf_isom_get_timescale(isom_file);
    u32 ret_gf_isom_get_copyright_count_xhhkf = gf_isom_get_copyright_count(NULL);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_copyright_count to gf_isom_set_track_flags
    Bool ret_gf_isom_has_keep_utc_times_ugeys = gf_isom_has_keep_utc_times(isom_file);
    u32 ret_gf_isom_get_next_alternate_group_id_ybauw = gf_isom_get_next_alternate_group_id(isom_file);

    GF_Err ret_gf_isom_set_track_flags_nyuna = gf_isom_set_track_flags(isom_file, ret_gf_isom_get_next_alternate_group_id_ybauw, ret_gf_isom_get_copyright_count_bxjqu, 0);

    // End mutation: Producer.APPEND_MUTATOR

    Bool ret_gf_isom_is_JPEG2000_ercrw = gf_isom_is_JPEG2000(isom_file);

    GF_Err ret_gf_isom_hevc_set_inband_config_gumuh = gf_isom_hevc_set_inband_config(isom_file, ret_gf_isom_get_timescale_uabxl, ret_gf_isom_get_copyright_count_xhhkf, ret_gf_isom_is_JPEG2000_ercrw);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_set_media_type(isom_file, trackNumber, new_media_type);

    cleanup_iso_file(isom_file);
    return 0;
}