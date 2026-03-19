#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for unlink, write, and close functions
#include <fcntl.h>  // Include for mkstemp function

extern "C" {
    extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
        // Define a temporary file name template
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd == -1) {
            return 0;
        }

        // Write the fuzzing data to the temporary file
        if (write(fd, data, size) != (ssize_t)size) {
            close(fd);
            unlink(tmpl);
            return 0;
        }
        close(fd);

        // Open the temporary file with libsndfile
        SF_INFO sfinfo;
        memset(&sfinfo, 0, sizeof(SF_INFO));
        SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
        if (sndfile == NULL) {
            unlink(tmpl);
            return 0;
        }

        // Call the function-under-test
        int error = sf_error(sndfile);

        // Clean up
        sf_close(sndfile);
        unlink(tmpl);

        return 0;
    }
}