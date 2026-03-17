#include <stdint.h>
#include <stddef.h>
#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
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

                // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_find_od_id_for_track with gf_isom_get_payt_count

                // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_get_payt_count with gf_isom_find_od_id_for_track
                gf_isom_find_od_id_for_track(file, track);
                // End mutation: Producer.REPLACE_FUNC_MUTATOR


                // End mutation: Producer.REPLACE_FUNC_MUTATOR



                // Close the ISO file

                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_find_od_id_for_track to gf_isom_has_meta_xml
                Bool ret_gf_isom_has_movie_lnvmt = gf_isom_has_movie(file);
                u32 ret_gf_isom_segment_get_fragment_count_hvylr = gf_isom_segment_get_fragment_count(NULL);

                u32 ret_gf_isom_has_meta_xml_mncbw = gf_isom_has_meta_xml(file, ret_gf_isom_has_movie_lnvmt, ret_gf_isom_segment_get_fragment_count_hvylr);

                // End mutation: Producer.APPEND_MUTATOR

                gf_isom_close(file);
            }

            // Remove the temporary file
            unlink(tmpl);
        }  }

    return 0;
}