#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

int LLVMFuzzerTestOneInput_291(const uint8_t *Data, size_t Size) {
    // Write fuzz data to a dummy file
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    GF_ISOFile *file = open_iso_file();
    if (!file) {
        return 0;
    }

    // Fuzz gf_isom_freeze_order
    gf_isom_freeze_order(file);

    // Fuzz gf_isom_set_byte_offset with a random offset
    if (Size >= sizeof(s64)) {
        s64 byte_offset = *(s64 *)Data;
        gf_isom_set_byte_offset(file, byte_offset);
    }

    // Fuzz gf_isom_enable_mfra

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_freeze_order to gf_isom_get_copyright
    u32 ret_gf_isom_guess_specification_niyzo = gf_isom_guess_specification(file);
    const char *krpapuza[1024] = {"bcgid", NULL};


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_new_track_from_template
    u32 ret_gf_isom_get_track_count_gvslr = gf_isom_get_track_count(file);
    u32 ret_gf_isom_get_next_alternate_group_id_umsqu = gf_isom_get_next_alternate_group_id(file);
    u32 ret_gf_isom_get_next_alternate_group_id_fxtvq = gf_isom_get_next_alternate_group_id(file);
    u8 ret_gf_isom_get_mode_twvap = gf_isom_get_mode(NULL);
    u32 ret_gf_isom_get_next_alternate_group_id_zgiwj = gf_isom_get_next_alternate_group_id(file);
    Bool ret_gf_isom_has_keep_utc_times_uuhwq = gf_isom_has_keep_utc_times(file);

    u32 ret_gf_isom_new_track_from_template_oegpc = gf_isom_new_track_from_template(file, ret_gf_isom_guess_specification_niyzo, ret_gf_isom_get_next_alternate_group_id_umsqu, ret_gf_isom_get_next_alternate_group_id_fxtvq, &ret_gf_isom_get_mode_twvap, ret_gf_isom_get_next_alternate_group_id_zgiwj, ret_gf_isom_has_keep_utc_times_uuhwq);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_get_copyright_clsfj = gf_isom_get_copyright(file, ret_gf_isom_guess_specification_niyzo, (const char **)"w", krpapuza);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_enable_mfra(file);

    // Fuzz gf_isom_last_error
    gf_isom_last_error(file);

    // Fuzz gf_isom_set_sample_group_in_traf
    gf_isom_set_sample_group_in_traf(file);

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(file);


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_byte_offset to gf_isom_subtitle_get_mime
        u32 ret_gf_isom_segment_get_fragment_count_nndcs = gf_isom_segment_get_fragment_count(NULL);
        u32 ret_gf_isom_get_next_alternate_group_id_iwnst = gf_isom_get_next_alternate_group_id(NULL);

        const char * ret_gf_isom_subtitle_get_mime_ldpkc = gf_isom_subtitle_get_mime(file, ret_gf_isom_segment_get_fragment_count_nndcs, ret_gf_isom_get_next_alternate_group_id_iwnst);
        if (ret_gf_isom_subtitle_get_mime_ldpkc == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    return 0;
}