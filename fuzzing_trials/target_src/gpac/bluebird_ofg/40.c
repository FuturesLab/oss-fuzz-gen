#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    if (size < sizeof(GF_ISOTrackID) + sizeof(u32) * 2 + sizeof(Bool) + 1) {
        return 0; // Ensure there's enough data for all parameters
    }

    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Fail gracefully if the movie cannot be opened
    }

    GF_ISOTrackID trakID = *(GF_ISOTrackID *)data;
    data += sizeof(GF_ISOTrackID);

    u32 MediaType = *(u32 *)data;
    data += sizeof(u32);

    u32 TimeScale = *(u32 *)data;
    data += sizeof(u32);

    Bool udta_only = *(Bool *)data;
    data += sizeof(Bool);

    u32 tk_box_size = size - (sizeof(GF_ISOTrackID) + sizeof(u32) * 2 + sizeof(Bool));
    u8 *tk_box = (u8 *)data;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_pssh_info
    u32 ret_gf_isom_text_sample_size_wozlt = gf_isom_text_sample_size(NULL);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_text_sample_size to gf_isom_ac3_config_new
    GF_AC3Config ojolpjmm;
    memset(&ojolpjmm, 0, sizeof(ojolpjmm));

    GF_Err ret_gf_isom_ac3_config_new_qtpto = gf_isom_ac3_config_new(NULL, ret_gf_isom_text_sample_size_wozlt, &ojolpjmm, NULL, (const char *)data, &ret_gf_isom_text_sample_size_wozlt);

    // End mutation: Producer.APPEND_MUTATOR

    u8 ret_gf_isom_get_mode_oxmot = gf_isom_get_mode(movie);
    const char cqlmezwh[1024] = "cwlxv";
    u32 ret_gf_isom_probe_file_bfwxu = gf_isom_probe_file(cqlmezwh);
    u32 ret_gf_isom_get_next_moof_number_pcfww = gf_isom_get_next_moof_number(movie);
    u32 cdpungjm;
    memset(&cdpungjm, 0, sizeof(cdpungjm));
    const bin128 *arrzsypm;
    memset(&arrzsypm, 0, sizeof(arrzsypm));

    GF_Err ret_gf_isom_get_pssh_info_cnsde = gf_isom_get_pssh_info(movie, ret_gf_isom_text_sample_size_wozlt, &ret_gf_isom_get_mode_oxmot, &cdpungjm, &ret_gf_isom_probe_file_bfwxu, &arrzsypm, NULL, &ret_gf_isom_get_next_moof_number_pcfww);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_new_track_from_template(movie, trakID, MediaType, TimeScale, tk_box, tk_box_size, udta_only);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_reset_alt_brands
    gf_isom_reset_alt_brands(movie);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}