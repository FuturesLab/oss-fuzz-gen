extern "C" {
    #include "sndfile.h"
    #include <unistd.h>  // for mkstemp, close, unlink
    #include <fcntl.h>   // for open
    #include "sys/types.h"
    #include <sys/stat.h>
    #include <stdint.h>  // for uint8_t
    #include <stddef.h>  // for size_t
    #include <stdio.h>   // for snprintf
    #include <stdlib.h>  // for mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    const char *error_message;

    // Initialize SF_INFO structure
    sfinfo.format = 0;

    // Create a temporary file to write the fuzz data
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

    // Close the file descriptor so that sndfile can open it
    close(fd);

    // Open the temporary file with sf_open
    sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        // If opening fails, we can still call sf_strerror with a NULL pointer
        error_message = sf_strerror(NULL);
    } else {
        // Call sf_strerror with the SNDFILE pointer
        error_message = sf_strerror(sndfile);
        sf_close(sndfile);
    }

    // Clean up the temporary file
    unlink(tmpl);

    // Return 0 as required by LLVMFuzzerTestOneInput
    return 0;
}