#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close() and unlink()
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Initialize htsFile for reading
    htsFile *file = hts_open(tmpl, "r");
    if (!file) {
        unlink(tmpl);
        return 0;
    }

    // Read the header from the file
    sam_hdr_t *hdr = sam_hdr_read(file);
    if (!hdr) {
        hts_close(file);
        unlink(tmpl);
        return 0;
    }

    // Clean up
    sam_hdr_destroy(hdr);
    hts_close(file);
    unlink(tmpl);

    return 0;
}