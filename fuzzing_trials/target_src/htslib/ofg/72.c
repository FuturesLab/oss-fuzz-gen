#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a SAM/BAM file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
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

    // Define index and format strings (non-NULL)
    const char *index_filename = "index.bai";
    const char *format = "bai";
    int flags = 0; // Example flag value

    // Call the function-under-test
    hts_idx_t *index = sam_index_load3(hts_file, tmpl, index_filename, flags);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }
    hts_close(hts_file);
    remove(tmpl);

    return 0;
}