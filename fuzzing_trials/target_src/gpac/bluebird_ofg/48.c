#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = GF_FALSE;
    u32 track_num = 1; // Initialize with a non-zero value

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file path
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Fuzz the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_track_kind
    u32 ret_gf_isom_get_supported_box_type_aelwc = gf_isom_get_supported_box_type(0);

    GF_Err ret_gf_isom_get_track_kind_hnrxu = gf_isom_get_track_kind(file, ret_gf_isom_get_supported_box_type_aelwc, 0, NULL, (char **)data);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_set_media_type

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_new_hint_description
    u32 ret_gf_isom_segment_get_fragment_count_wlhrq = gf_isom_segment_get_fragment_count(file);
    u8 ret_gf_isom_get_mode_vskyc = gf_isom_get_mode(file);
    u32 ret_gf_isom_get_timescale_qqlew = gf_isom_get_timescale(file);

    GF_Err ret_gf_isom_new_hint_description_xlive = gf_isom_new_hint_description(file, ret_gf_isom_segment_get_fragment_count_wlhrq, 0, 0, ret_gf_isom_get_mode_vskyc, &ret_gf_isom_get_timescale_qqlew);

    // End mutation: Producer.APPEND_MUTATOR

    u32 ret_gf_isom_probe_file_qocex = gf_isom_probe_file((const char *)"r");


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_probe_file to gf_isom_enum_track_group
    u32 ret_gf_isom_segment_get_fragment_count_qswcs = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_get_copyright_count_onwtc = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_supported_box_type_illgd = gf_isom_get_supported_box_type(0);
    u32 ret_gf_isom_get_next_moof_number_cjpra = gf_isom_get_next_moof_number(file);

    Bool ret_gf_isom_enum_track_group_qegzp = gf_isom_enum_track_group(file, ret_gf_isom_get_copyright_count_onwtc, &ret_gf_isom_get_supported_box_type_illgd, &ret_gf_isom_probe_file_qocex, &ret_gf_isom_get_next_moof_number_cjpra);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_yclea = gf_isom_set_media_type(file, ret_gf_isom_probe_file_qocex, 0);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_media_type to gf_isom_change_mpeg4_description
    u32 ret_gf_isom_segment_get_fragment_count_ubecv = gf_isom_segment_get_fragment_count(file);
    u32 ret_gf_isom_guess_specification_fwzkg = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_change_mpeg4_description_hvqrq = gf_isom_change_mpeg4_description(file, ret_gf_isom_segment_get_fragment_count_ubecv, ret_gf_isom_guess_specification_fwzkg, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}