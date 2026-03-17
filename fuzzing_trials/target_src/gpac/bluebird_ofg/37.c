#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_has_meta_xml with gf_isom_get_meta_primary_item_id

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_trex_template
    u32 ret_gf_isom_get_pssh_count_rilwb = gf_isom_get_pssh_count(file);
    u8 *vnonukuq;
    memset(&vnonukuq, 0, sizeof(vnonukuq));

    GF_Err ret_gf_isom_get_trex_template_pqbfv = gf_isom_get_trex_template(file, 0, &vnonukuq, &ret_gf_isom_get_pssh_count_rilwb);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_trex_template to gf_isom_get_sample_description_index
    u32 ret_gf_isom_get_next_alternate_group_id_upxhg = gf_isom_get_next_alternate_group_id(file);
    u64 ret_gf_isom_get_first_mdat_start_kxtqg = gf_isom_get_first_mdat_start(file);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_sample_description_index with gf_isom_get_sample_from_dts
    u32 ret_gf_isom_get_sample_description_index_kjbnj = gf_isom_get_sample_from_dts(file, ret_gf_isom_get_next_alternate_group_id_upxhg, ret_gf_isom_get_first_mdat_start_kxtqg);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_get_meta_primary_item_id(file, root_meta, track_num);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}