#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For mkstemp, write, close, unlink
#include <htslib/hts.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    hts_idx_t *index = sam_index_load(hts_file, tmpl);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}