#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sndfile.h>

extern "C" {
    #include <unistd.h>
    #include <fcntl.h>
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an audio file.
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file.
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile.
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        // Clean up the temporary file.
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test.
    sf_perror(sndfile);

    // Clean up.
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}