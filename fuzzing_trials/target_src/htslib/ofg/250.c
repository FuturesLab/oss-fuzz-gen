#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary file to be used with hts_open
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Open the temporary file with hts_open
    htsFile *file = hts_open(tmpl, "w");
    if (file == NULL) {
        return 0;
    }

    // Extract an int from the data
    int cache_size = *((int *)data);

    // Call the function-under-test
    hts_set_cache_size(file, cache_size);

    // Clean up
    hts_close(file);
    remove(tmpl);

    return 0;
}