#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // Include this for close() and write()
#include <fcntl.h>   // Include this for mkstemp()
#include <htslib/sam.h>
#include <htslib/bgzf.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
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

    // Open the temporary file with BGZF
    BGZF *bgzf = bgzf_open(tmpl, "r");
    if (bgzf == NULL) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *b = bam_init1();
    if (b == NULL) {
        bgzf_close(bgzf);
        return 0;
    }

    // Call the function-under-test
    bam_read1(bgzf, b);

    // Clean up
    bam_destroy1(b);
    bgzf_close(bgzf);
    remove(tmpl);

    return 0;
}