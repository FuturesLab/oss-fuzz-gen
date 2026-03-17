#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
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
    u32 ret_gf_isom_get_copyright_count_hweto = gf_isom_get_copyright_count(file);
    u32 ret_gf_isom_probe_file_qdgtc = gf_isom_probe_file((const char *)"w");

    GF_Err ret_gf_isom_change_ismacryp_protection_bfoic = gf_isom_change_ismacryp_protection(file, ret_gf_isom_get_copyright_count_hweto, ret_gf_isom_probe_file_qdgtc, NULL, NULL);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_change_ismacryp_protection to gf_isom_get_sidx_duration
    u64 ret_gf_isom_get_duration_chwsn = gf_isom_get_duration(file);
    const char fstglcwi[1024] = "hvjll";
    u32 ret_gf_isom_probe_file_ijbar = gf_isom_probe_file(fstglcwi);

    GF_Err ret_gf_isom_get_sidx_duration_cuira = gf_isom_get_sidx_duration(file, &ret_gf_isom_get_duration_chwsn, &ret_gf_isom_probe_file_ijbar);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}