#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
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
    gf_isom_close(file);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_close to gf_isom_setup_hint_track
    u32 ret_gf_isom_get_timescale_slvqg = gf_isom_get_timescale(NULL);

    GF_Err ret_gf_isom_setup_hint_track_nmhwl = gf_isom_setup_hint_track(file, ret_gf_isom_get_timescale_slvqg, 0);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}