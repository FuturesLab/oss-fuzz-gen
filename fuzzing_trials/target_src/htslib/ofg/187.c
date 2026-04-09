#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/sam.h>
#include <htslib/bgzf.h>

int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }
    close(fd);

    // Open the temporary file using BGZF
    BGZF *bgzf = bgzf_open(tmpl, "r");
    if (bgzf == NULL) {
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Create a bam1_t structure
    bam1_t *b = bam_init1();
    if (b == NULL) {
        bgzf_close(bgzf);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Call the function-under-test
    int result = bam_read1(bgzf, b);

    // Clean up
    bam_destroy1(b);
    bgzf_close(bgzf);
    unlink(tmpl); // Remove the temporary file

    return 0;
}