#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using htslib
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_read(hts_file);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    hts_close(hts_file);
    remove(tmpl);

    return 0;
}