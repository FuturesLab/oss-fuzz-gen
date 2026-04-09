#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For close() and remove()
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
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

    // Open the file as a samFile
    samFile *sam = sam_open(tmpl, "r");
    if (sam == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *header = sam_hdr_get(sam);

    // Clean up
    if (header != NULL) {
        sam_hdr_destroy(header);
    }
    sam_close(sam);
    remove(tmpl);

    return 0;
}