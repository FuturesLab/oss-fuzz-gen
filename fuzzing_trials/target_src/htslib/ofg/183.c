#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for 'close', 'unlink', and 'write'
#include <fcntl.h>  // Include for 'mkstemp'
#include <htslib/sam.h>
#include <htslib/bgzf.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a BGZF file
    BGZF *bgzf = bgzf_open(tmpl, "r");
    if (bgzf == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *hdr = bam_hdr_read(bgzf);

    // Clean up
    if (hdr != NULL) {
        sam_hdr_destroy(hdr);
    }
    bgzf_close(bgzf);
    unlink(tmpl);

    return 0;
}