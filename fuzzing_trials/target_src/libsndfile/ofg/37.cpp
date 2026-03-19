#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and write()

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor so that sndfile can open it
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        remove(tmpl);
        return 0;
    }

    // Buffer to store the error string
    size_t err_buf_size = 256;
    char *err_buf = (char *)malloc(err_buf_size);
    if (err_buf == NULL) {
        sf_close(sndfile);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_error_str(sndfile, err_buf, err_buf_size);

    // Clean up
    free(err_buf);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}