#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a sound file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        // If the file cannot be opened, clean up and return
        unlink(tmpl);
        return 0;
    }

    // Prepare a buffer to store the error string
    char error_str[256];
    size_t error_str_size = sizeof(error_str);

    // Call the function-under-test
    sf_error_str(sndfile, error_str, error_str_size);

    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}