#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // Include this for close() and unlink()
#include <fcntl.h>   // Include this for mkstemp()
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a samFile
    samFile *sam = sam_open(tmpl, "r");
    if (sam == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_read(sam);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    sam_close(sam);
    unlink(tmpl);

    return 0;
}