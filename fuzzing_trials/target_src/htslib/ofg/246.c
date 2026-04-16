#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this for the unlink() and close() functions
#include <fcntl.h>   // Include this for the mkstemp() function
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Open the file as an htsFile
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Call the function-under-test
    hts_idx_t *index = sam_index_load(hts_file, tmpl);

    // Cleanup
    if (index != NULL) {
        hts_idx_destroy(index);
    }
    hts_close(hts_file);
    unlink(tmpl); // Remove the temporary file

    return 0;
}