#include <stdint.h>
#include <stddef.h>
#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    GF_ISOFile *file = NULL;
    u32 track = 1;  // Initialize track with a non-zero value

    // Check if the size is sufficient to create a valid ISO file
    if (size > 0) {
        // Create a temporary file to store the input data
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            // Write data to the temporary file
            write(fd, data, size);
            close(fd);

            // Open the file as an ISO file
            file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
            if (file != NULL) {
                // Call the function-under-test
                gf_isom_find_od_id_for_track(file, track);

                // Close the ISO file

                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_find_od_id_for_track to gf_isom_is_track_in_root_od
                u32 ret_gf_isom_get_supported_box_type_sbxcv = gf_isom_get_supported_box_type(0);


                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_get_supported_box_type to gf_isom_rtp_packet_begin
                Bool ret_gf_isom_is_smooth_streaming_moov_mhihe = gf_isom_is_smooth_streaming_moov(file);
                u8 ret_gf_isom_get_mode_xantt = gf_isom_get_mode(NULL);
                u8 ret_gf_isom_get_mode_shhqu = gf_isom_get_mode(file);
                u8 ret_gf_isom_get_mode_fmtcp = gf_isom_get_mode(NULL);
                u8 ret_gf_isom_get_mode_fzfrh = gf_isom_get_mode(file);

                GF_Err ret_gf_isom_rtp_packet_begin_rpkfe = gf_isom_rtp_packet_begin(file, ret_gf_isom_get_supported_box_type_sbxcv, 0, 0, ret_gf_isom_get_mode_xantt, ret_gf_isom_get_mode_shhqu, ret_gf_isom_get_mode_fmtcp, ret_gf_isom_get_mode_fzfrh, 0, 0);

                // End mutation: Producer.APPEND_MUTATOR

                u8 ret_gf_isom_is_track_in_root_od_wvsxl = gf_isom_is_track_in_root_od(file, ret_gf_isom_get_supported_box_type_sbxcv);

                // End mutation: Producer.APPEND_MUTATOR

                gf_isom_close(file);
            }

            // Remove the temporary file
            unlink(tmpl);
        }   }

    return 0;
}