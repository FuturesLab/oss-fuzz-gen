#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <htslib/sam.h>
#include <htslib/bgzf.h>

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for meaningful data
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to act as a BGZF file
    char tmpl[] = "/tmp/fuzzbgzfXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file with BGZF
    BGZF *bgzf = bgzf_fdopen(fd, "w");
    if (bgzf == NULL) {
        close(fd);
        return 0;
    }

    // Allocate memory for sam_hdr_t and initialize it
    sam_hdr_t *sam_hdr = sam_hdr_init();
    if (sam_hdr == NULL) {
        bgzf_close(bgzf);
        close(fd);
        return 0;
    }

    // Create a dummy header text
    char header_text[] = "@HD\tVN:1.0\tSO:unsorted\n";
    if (sam_hdr_add_lines(sam_hdr, header_text, strlen(header_text)) != 0) {
        sam_hdr_destroy(sam_hdr);
        bgzf_close(bgzf);
        close(fd);
        return 0;
    }

    // Call the function-under-test
    bam_hdr_write(bgzf, sam_hdr);

    // Clean up
    sam_hdr_destroy(sam_hdr);
    bgzf_close(bgzf);
    close(fd);
    unlink(tmpl);

    return 0;
}