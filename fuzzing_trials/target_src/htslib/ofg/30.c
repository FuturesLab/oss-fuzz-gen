#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hfile.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file using hFILE
    hFILE *file = hopen(tmpl, "rb");
    if (file == NULL) {
        return 0;
    }

    // Prepare a format string and htsFormat structure
    const char *format_str = "test_format";
    htsFormat format;

    // Call the function-under-test
    hts_detect_format2(file, format_str, &format);

    // Clean up
    hclose(file);
    remove(tmpl);

    return 0;
}