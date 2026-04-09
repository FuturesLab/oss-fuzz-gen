#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

// Fuzzer entry point
int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an htsFile
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

    // Close the file descriptor so it can be reopened by hts_open
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        return 0;
    }

    // Call the function under test
    sam_idx_save(hts_file);

    // Close the htsFile
    hts_close(hts_file);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}