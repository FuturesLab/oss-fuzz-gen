#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // For mkstemp, write, close, and unlink
#include <htslib/hts.h>
#include <htslib/tbx.h>
#include <htslib/sam.h>  // For bam_hdr_t, bam1_t, etc.

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    if (size < 16) {
        // Not enough data to extract meaningful parameters
        return 0;
    }

    // Create a temporary file to use as a filename argument
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);
    if (fd1 == -1 || fd2 == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd1, data, size);
    write(fd2, data, size);

    // Close the file descriptors
    close(fd1);
    close(fd2);

    // Interpret the first 16 bytes of data as parameters for hts_idx_init
    int min_shift = data[0] % 16; // Ensure a reasonable range
    int n_lvls = data[1] % 16;    // Ensure a reasonable range
    uint64_t seed = *(uint64_t *)(data + 2);

    // Initialize hts_idx_t object with fuzzed parameters
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, min_shift, n_lvls, seed);

    // Check if the index was initialized successfully
    if (!idx) {
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    // Open the temporary files for reading
    htsFile *hts_fp1 = hts_open(tmpl1, "r");
    htsFile *hts_fp2 = hts_open(tmpl2, "r");
    if (!hts_fp1 || !hts_fp2) {
        hts_idx_destroy(idx);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    // Call the function-under-test with the temporary files
    int result = hts_idx_save_as(idx, tmpl1, tmpl2, HTS_FMT_CSI);

    // Clean up
    hts_close(hts_fp1);
    hts_close(hts_fp2);
    hts_idx_destroy(idx);
    unlink(tmpl1);
    unlink(tmpl2);

    return result == 0 ? 0 : 1; // Return 0 if successful, 1 otherwise
}