#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include this for close() and unlink()
#include <string.h> // Include this for memcpy()
#include <fcntl.h>  // Include this for open() and O_WRONLY
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzer's input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as an htsFile for reading
    htsFile *hts_fp = hts_open(tmpl, "r");
    if (!hts_fp) {
        unlink(tmpl);
        return 0;
    }

    // Read the header from the file
    sam_hdr_t *hdr = sam_hdr_read(hts_fp);
    if (!hdr) {
        hts_close(hts_fp);
        unlink(tmpl);
        return 0;
    }

    // Perform operations on the header if needed
    // For example, write it back to another file or manipulate it

    // Clean up
    sam_hdr_destroy(hdr);
    hts_close(hts_fp);
    unlink(tmpl); // Remove the temporary file

    return 0;
}