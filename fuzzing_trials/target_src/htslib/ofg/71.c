#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for the close() and remove() functions
#include <htslib/hts.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (!hts_file) {
        remove(tmpl);
        return 0;
    }

    // Define index and format strings
    const char *index = "index.bai"; // Example index filename
    const char *format = "bai";      // Example format

    // Call the function-under-test
    hts_idx_t *index_result = sam_index_load3(hts_file, tmpl, index, 0);

    // Clean up
    if (index_result) {
        hts_idx_destroy(index_result);
    }
    hts_close(hts_file);
    remove(tmpl);

    return 0;
}