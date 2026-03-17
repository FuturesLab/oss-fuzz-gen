#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include "/src/gpac/include/gpac/isomedia.h"
#include "/src/gpac/include/gpac/constants.h"

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
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
    u32 ret_gf_isom_text_sample_size_sdtfa = gf_isom_text_sample_size(NULL);
    u32 ret_gf_isom_probe_file_pejsm = gf_isom_probe_file((const char *)data);
    char vhmclywm[1024] = "hloap";


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_probe_file to gf_isom_get_sample_for_movie_time
    u32 ret_gf_isom_get_timescale_kluij = gf_isom_get_timescale(file);
    u32 ret_gf_isom_segment_get_fragment_count_prrqo = gf_isom_segment_get_fragment_count(NULL);
    u64 ret_gf_isom_get_duration_evexg = gf_isom_get_duration(file);
    u64 ret_gf_isom_get_first_mdat_start_zgzdn = gf_isom_get_first_mdat_start(NULL);
    GF_ISOSample *qmpbrgbh;
    memset(&qmpbrgbh, 0, sizeof(qmpbrgbh));

    GF_Err ret_gf_isom_get_sample_for_movie_time_nsblh = gf_isom_get_sample_for_movie_time(file, ret_gf_isom_segment_get_fragment_count_prrqo, ret_gf_isom_get_duration_evexg, &ret_gf_isom_probe_file_pejsm, 0, &qmpbrgbh, &ret_gf_isom_probe_file_pejsm, &ret_gf_isom_get_first_mdat_start_zgzdn);

    // End mutation: Producer.APPEND_MUTATOR

    GF_Err ret_gf_isom_change_ismacryp_protection_tukzj = gf_isom_change_ismacryp_protection(file, ret_gf_isom_text_sample_size_sdtfa, ret_gf_isom_probe_file_pejsm, (char *)data, vhmclywm);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_has_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}