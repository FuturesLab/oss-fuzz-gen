#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for close() and unlink()
#include <stdlib.h>  // Include for mkstemp()
#include <htslib/sam.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Create a temporary file to use as input for htsFile
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

    // Open the temporary file with hts_open
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Initialize a sam_hdr_t object
    sam_hdr_t *sam_header = sam_hdr_init();
    if (sam_header == NULL) {
        hts_close(hts_file);
        unlink(tmpl);
        return 0;
    }

    // Define an integer option for sam_idx_init
    int option = 0; // This can be varied as needed

    // Define a non-NULL string for the fourth parameter
    const char *arg_str = "example_arg";

    // Call the function-under-test
    sam_idx_init(hts_file, sam_header, option, arg_str);

    // Clean up
    sam_hdr_destroy(sam_header);
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}