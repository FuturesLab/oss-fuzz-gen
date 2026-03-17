#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"
#include "/src/gpac/include/gpac/isomedia.h" // Assuming the library header for gf_isom_dump_supported_box

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an index
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract the index from the input data
    uint32_t idx = *(const uint32_t *)data;

    // Check if the index is within a valid range
    // Assuming there's a known maximum number of supported boxes
    uint32_t max_supported_boxes = 100; // This value should be determined based on the library's documentation or implementation
    if (idx >= max_supported_boxes) {
        return 0;
    }

    // Create a temporary file to use as the FILE* parameter
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file as a FILE* stream
    FILE *trace = fdopen(fd, "w+");
    if (!trace) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    gf_isom_dump_supported_box(idx, trace);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_dump_supported_box to gf_isom_dump_hint_sample
    u32 ret_gf_isom_probe_file_xebby = gf_isom_probe_file((const char *)data);
    u32 ret_gf_isom_text_sample_size_qpinw = gf_isom_text_sample_size(NULL);

    GF_Err ret_gf_isom_dump_hint_sample_vtzuz = gf_isom_dump_hint_sample(NULL, ret_gf_isom_probe_file_xebby, ret_gf_isom_text_sample_size_qpinw, trace);

    // End mutation: Producer.APPEND_MUTATOR

    fclose(trace);
    unlink(tmpl);

    return 0;
}