#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close() and unlink()
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h" // For hts_idx_t
#include "/src/htslib/htslib/bgzf.h" // For bgzf_t
#include "htslib/sam.h" // For bam_hdr_t, bam1_t

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for hts_idx_save
    // Instead of allocating hts_idx_t directly, we will use a function that returns a valid index
    // For demonstration purposes, we will create a simple BAM index
    hts_idx_t *idx = bam_index_load("example.bam"); // Load an example BAM index
    if (idx == NULL) {
        return 0; // Failed to load index, exit the fuzzer
    }

    // Create a temporary filename to pass to hts_idx_save
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        hts_idx_destroy(idx);
        return 0; // Failed to create a temporary file, exit the fuzzer
    }
    close(fd); // Close the file descriptor as we only need the filename

    // Use the first byte of data as the int parameter, or default to 0
    int int_param = (size > 0) ? data[0] : 0;

    // Call the function-under-test
    if (hts_idx_save(idx, tmpl, int_param) != 0) {
        // Handle the error if needed
    }

    // Clean up
    hts_idx_destroy(idx);
    unlink(tmpl); // Remove the temporary file

    return 0;
}