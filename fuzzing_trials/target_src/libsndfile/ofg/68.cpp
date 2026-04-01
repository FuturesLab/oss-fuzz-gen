#include <sndfile.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a sound file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor and reopen it with libsndfile
    close(fd);

    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Define a non-zero sf_count_t offset and a valid whence value
    sf_count_t offset = 1; // Non-zero offset
    int whence = SF_SEEK_SET; // Valid whence value

    // Call the function-under-test
    sf_count_t result = sf_seek(sndfile, offset, whence);

    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}