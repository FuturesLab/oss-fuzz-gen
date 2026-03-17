#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
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
    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_set_media_type
    u32 ret_gf_isom_get_copyright_count_stkec = gf_isom_get_copyright_count(NULL);
    u32 ret_gf_isom_get_pssh_count_kcofv = gf_isom_get_pssh_count(file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_pssh_count to gf_isom_sdp_add_track_line
    u32 ret_gf_isom_segment_get_fragment_count_txsif = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_sdp_add_track_line_hfipm = gf_isom_sdp_add_track_line(file, ret_gf_isom_segment_get_fragment_count_txsif, NULL);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_sdp_add_track_line to gf_isom_get_last_producer_time_box
    u32 ret_gf_isom_get_copyright_count_fjucy = gf_isom_get_copyright_count(NULL);
    u64 ret_gf_isom_get_first_mdat_start_fcbzc = gf_isom_get_first_mdat_start(file);
    u64 ret_gf_isom_get_duration_fadxl = gf_isom_get_duration(file);
    Bool ret_gf_isom_moov_first_ezjak = gf_isom_moov_first(file);

    Bool ret_gf_isom_get_last_producer_time_box_yqiga = gf_isom_get_last_producer_time_box(file, ret_gf_isom_get_copyright_count_fjucy, &ret_gf_isom_get_first_mdat_start_fcbzc, &ret_gf_isom_get_duration_fadxl, ret_gf_isom_moov_first_ezjak);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_set_media_type_tfhjl = gf_isom_set_media_type(file, ret_gf_isom_get_copyright_count_stkec, ret_gf_isom_get_pssh_count_kcofv);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}