#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/hfile.h"

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to extract meaningful strings
    if (size < 4) { // Adjust size check to ensure enough space for null-termination
        return 0;
    }

    // Create a temporary file to use with hts_hopen
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the temporary file using hFILE
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        remove(tmpl);
        return 0;
    }

    // Extract strings from the data for mode and format
    char mode[2] = {0}; // Ensure mode is null-terminated
    char format[2] = {0}; // Ensure format is null-terminated

    mode[0] = data[1];
    format[0] = data[2];

    // Call the function under test
    htsFile *htsfile = hts_hopen(hfile, mode, format);

    // Clean up
    if (htsfile != NULL) {
        hts_close(htsfile);
    } else {
        hclose(hfile);
    }
    remove(tmpl);

    return 0;
}