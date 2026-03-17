#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
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
    u32 ret_gf_isom_get_next_moof_number_hnobj = gf_isom_get_next_moof_number(file);
    u32 ret_gf_isom_guess_specification_cnshv = gf_isom_guess_specification(file);

    GF_Err ret_gf_isom_set_media_type_btvuh = gf_isom_set_media_type(file, ret_gf_isom_get_next_moof_number_hnobj, ret_gf_isom_guess_specification_cnshv);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_media_type to gf_isom_extract_meta_item

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_set_media_type to gf_isom_disable_brand_rewrite
    Bool ret_gf_isom_is_JPEG2000_lmcli = gf_isom_is_JPEG2000(file);

    GF_Err ret_gf_isom_disable_brand_rewrite_imeyd = gf_isom_disable_brand_rewrite(file, ret_gf_isom_is_JPEG2000_lmcli);

    // End mutation: Producer.APPEND_MUTATOR

    Bool ret_gf_isom_needs_layer_reconstruction_avrlq = gf_isom_needs_layer_reconstruction(file);
    u32 ret_gf_isom_get_copyright_count_qwzdi = gf_isom_get_copyright_count(NULL);
    u32 ret_gf_isom_segment_get_fragment_count_harql = gf_isom_segment_get_fragment_count(file);

    GF_Err ret_gf_isom_extract_meta_item_hqsns = gf_isom_extract_meta_item(file, ret_gf_isom_needs_layer_reconstruction_avrlq, ret_gf_isom_get_copyright_count_qwzdi, ret_gf_isom_segment_get_fragment_count_harql, (const char *)"w");

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}