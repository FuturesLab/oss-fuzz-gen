#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the file using htslib
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_read(file);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    hts_close(file);
    unlink(tmpl);

    return 0;
}