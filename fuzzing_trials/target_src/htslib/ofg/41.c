#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Call the function-under-test with the temporary file
    int options = HTS_IDX_SAVE_REMOTE; // Example option, adjust as needed
    hts_idx_t *idx = hts_idx_load(tmpl, options);

    // Clean up
    if (idx != NULL) {
        hts_idx_destroy(idx);
    }
    unlink(tmpl);

    return 0;
}