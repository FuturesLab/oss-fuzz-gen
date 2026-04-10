#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close() and unlink()
#include <fcntl.h>     // For mkstemp()
#include <sys/types.h> // For size_t
#include <sys/stat.h>  // For open()
#include <htslib/sam.h>
#include <htslib/bgzf.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
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

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a BGZF file
    BGZF *bgzf = bgzf_open(tmpl, "r");
    if (bgzf == NULL) {
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *header = bam_hdr_read(bgzf);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    bgzf_close(bgzf);

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}