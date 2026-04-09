#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and unlink()
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/hts_log.h>
#include <htslib/hts_os.h>
#include <htslib/faidx.h> // Corrected include path for hts_idx_t and related functions

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a filename and some data
    if (size < 10) {
        return 0;
    }

    // Create a temporary file for the index
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Initialize hts_idx_t structure
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);
    if (idx == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Copy some data to a valid filename string
    char filename[256];
    snprintf(filename, sizeof(filename), "%s", tmpl);

    // Use a fixed value for int argument
    int fmt = HTS_FMT_CSI;

    // Use the input data to simulate a real-world scenario
    // Feed part of the data to the index
    size_t data_to_use = size - 5; // Use part of the data
    if (data_to_use > 0) {
        hts_idx_push(idx, 0, data[0], data[1], data[2], 0);
    }

    // Call the function-under-test
    hts_idx_save(idx, filename, fmt);

    // Clean up
    hts_idx_destroy(idx);
    unlink(tmpl);

    return 0;
}