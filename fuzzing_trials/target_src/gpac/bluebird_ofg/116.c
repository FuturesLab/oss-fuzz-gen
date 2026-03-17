#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_enum_sample_group
    u32 ret_gf_isom_text_sample_size_wkdlv = gf_isom_text_sample_size(NULL);
    u32 ret_gf_isom_get_copyright_count_qvhwa = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_get_timescale_daxbi = gf_isom_get_timescale(NULL);
    u32 ret_gf_isom_segment_get_fragment_count_ecklv = gf_isom_segment_get_fragment_count(file);
    const char mrjhjaxr[1024] = "uvduz";
    u32 ret_gf_isom_probe_file_zwveq = gf_isom_probe_file(mrjhjaxr);
    u32 ret_gf_isom_get_next_moof_number_zttxj = gf_isom_get_next_moof_number(NULL);
    u32 ret_gf_isom_get_next_moof_number_vebvl = gf_isom_get_next_moof_number(NULL);
    u8 *secjyico;
    memset(&secjyico, 0, sizeof(secjyico));

    GF_Err ret_gf_isom_enum_sample_group_jushk = gf_isom_enum_sample_group(file, ret_gf_isom_text_sample_size_wkdlv, ret_gf_isom_get_copyright_count_qvhwa, &ret_gf_isom_get_timescale_daxbi, &ret_gf_isom_segment_get_fragment_count_ecklv, &ret_gf_isom_probe_file_zwveq, &ret_gf_isom_get_next_moof_number_zttxj, &secjyico, &ret_gf_isom_get_next_moof_number_vebvl);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}