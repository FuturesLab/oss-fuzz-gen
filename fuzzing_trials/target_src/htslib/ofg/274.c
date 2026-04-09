#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
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

    // Open the temporary file using hts_open
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    const htsFormat *format = hts_get_format(file);

    // Clean up
    hts_close(file);
    remove(tmpl);

    return 0;
}