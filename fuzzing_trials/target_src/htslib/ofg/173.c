#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close() and write()
#include <stdio.h>   // Include for remove()
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
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

    // Close the file descriptor
    close(fd);

    // Open the temporary file using hts_open
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = hts_check_EOF(file);

    // Close the htsFile
    hts_close(file);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}