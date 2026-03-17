#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_get_payt_info
    u32 ret_gf_isom_get_track_count_tagqe = gf_isom_get_track_count(file);

    const char * ret_gf_isom_get_payt_info_yjimh = gf_isom_get_payt_info(file, ret_gf_isom_get_track_count_tagqe, 0, NULL);
    if (ret_gf_isom_get_payt_info_yjimh == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_set_media_type

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of gf_isom_probe_file
    u32 ret_gf_isom_probe_file_kgarh = gf_isom_probe_file((const char *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR




    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_set_media_type with gf_isom_check_data_reference
    GF_Err ret_gf_isom_set_media_type_hyfku = gf_isom_check_data_reference(file, ret_gf_isom_probe_file_kgarh, 0);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}