#include <sndfile.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Reset the file descriptor offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    sfinfo.format = 0; // Let the library determine the format

    // Call the function-under-test
    SNDFILE *sndfile = sf_open_fd(fd, SFM_READ, &sfinfo, 0);

    // Clean up
    if (sndfile != NULL) {
        sf_close(sndfile);
    }
    close(fd);
    unlink(tmpl);

    return 0;
}