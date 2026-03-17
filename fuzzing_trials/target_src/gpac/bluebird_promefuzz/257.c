#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "/src/gpac/include/gpac/isomedia.h"

static GF_ISOFile* open_iso_file() {
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_READ, NULL);
    return file;
}

int LLVMFuzzerTestOneInput_257(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_track_count to gf_isom_mvc_config_new
    gf_isom_disable_inplace_rewrite(file);
    u32 ret_gf_isom_get_next_alternate_group_id_gxhme = gf_isom_get_next_alternate_group_id(file);
    GF_AVCConfig yittcmyw;
    memset(&yittcmyw, 0, sizeof(yittcmyw));
    const char hdsiyvjb[1024] = "imhyt";


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_mvc_config_new with gf_isom_svc_config_new
    GF_Err ret_gf_isom_mvc_config_new_cllda = gf_isom_svc_config_new(file, ret_gf_isom_get_track_count_gvslr, &yittcmyw, (const char *)"r", hdsiyvjb, &ret_gf_isom_get_next_alternate_group_id_gxhme);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_svc_config_new to gf_isom_get_jp2_config
    u64 ret_gf_isom_get_first_mdat_start_anxwe = gf_isom_get_first_mdat_start(file);
    u32 ret_gf_isom_get_next_alternate_group_id_uptgu = gf_isom_get_next_alternate_group_id(file);
    u32 ret_gf_isom_get_next_moof_number_erlcl = gf_isom_get_next_moof_number(file);
    u8 *uneatras;
    memset(&uneatras, 0, sizeof(uneatras));

    GF_Err ret_gf_isom_get_jp2_config_zvzem = gf_isom_get_jp2_config(file, ret_gf_isom_get_next_alternate_group_id_uptgu, ret_gf_isom_get_next_moof_number_erlcl, &uneatras, &ret_gf_isom_get_next_alternate_group_id_gxhme);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_get_next_alternate_group_id_umsqu = gf_isom_get_next_alternate_group_id(file);
    u32 ret_gf_isom_get_next_alternate_group_id_fxtvq = gf_isom_get_next_alternate_group_id(file);
    u8 ret_gf_isom_get_mode_twvap = gf_isom_get_mode(NULL);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_next_alternate_group_id with gf_isom_guess_specification
    u32 ret_gf_isom_get_next_alternate_group_id_zgiwj = gf_isom_guess_specification(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

    gf_isom_close(file);
    return 0;
}