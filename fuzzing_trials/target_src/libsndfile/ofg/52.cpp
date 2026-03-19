#include <stdint.h>
#include <stdlib.h>
#include <sndfile.h>

extern "C" {
    #include <unistd.h>
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Initialize variables
    SNDFILE *sndfile = NULL;
    SF_INFO sfinfo;
    sfinfo.format = 0; // Initialize to zero as required by libsndfile

    // Create a temporary file to hold the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor, as sf_open will open it again
    close(fd);

    // Open the temporary file with libsndfile
    sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        return 0;
    }

    // Fuzz the sf_get_string function
    const char *result = sf_get_string(sndfile, SF_STR_TITLE);

    // Cleanup
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}