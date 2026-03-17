#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_add_sample_group_info
    u32 ret_gf_isom_get_copyright_count_ordrt = gf_isom_get_copyright_count(NULL);
    u32 ret_gf_isom_segment_get_fragment_count_mmhrc = gf_isom_segment_get_fragment_count(NULL);
    u64 ret_gf_isom_get_unused_box_bytes_yvwph = gf_isom_get_unused_box_bytes(file);
    u32 ret_gf_isom_probe_file_rlldg = gf_isom_probe_file((const char *)"r");
    Bool ret_gf_isom_is_inplace_rewrite_vfdhb = gf_isom_is_inplace_rewrite(NULL);
    u32 ret_gf_isom_get_copyright_count_wrghi = gf_isom_get_copyright_count(file);

    GF_Err ret_gf_isom_add_sample_group_info_kupwv = gf_isom_add_sample_group_info(file, ret_gf_isom_get_copyright_count_ordrt, ret_gf_isom_segment_get_fragment_count_mmhrc, (void *)file, ret_gf_isom_probe_file_rlldg, ret_gf_isom_is_inplace_rewrite_vfdhb, &ret_gf_isom_get_copyright_count_wrghi);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_enable_mfra
    gf_isom_enable_mfra(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}