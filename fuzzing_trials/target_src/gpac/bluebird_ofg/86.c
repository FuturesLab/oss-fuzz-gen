#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_change_ismacryp_protection

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function gf_isom_guess_specification with gf_isom_get_copyright_count
    u32 ret_gf_isom_guess_specification_demzn = gf_isom_get_copyright_count(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    GF_Err ret_gf_isom_change_ismacryp_protection_cczwo = gf_isom_change_ismacryp_protection(file, ret_gf_isom_guess_specification_demzn, 0, (char *)data, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}