#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_close with gf_isom_sdp_clean

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_has_meta_xml to gf_isom_enable_compression
    u32 ret_gf_isom_guess_specification_pksps = gf_isom_guess_specification(file);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_guess_specification to gf_isom_get_pcm_config
    u32 ret_gf_isom_get_timescale_pjjyo = gf_isom_get_timescale(file);
    u32 ret_gf_isom_get_next_moof_number_djayy = gf_isom_get_next_moof_number(file);

    GF_Err ret_gf_isom_get_pcm_config_jpkyi = gf_isom_get_pcm_config(NULL, ret_gf_isom_get_timescale_pjjyo, ret_gf_isom_guess_specification_pksps, &ret_gf_isom_get_next_moof_number_djayy, &ret_gf_isom_guess_specification_pksps);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_enable_compression_tvdqj = gf_isom_enable_compression(file, 0, ret_gf_isom_guess_specification_pksps);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_sdp_clean(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    unlink(tmpl);

    return 0;
}