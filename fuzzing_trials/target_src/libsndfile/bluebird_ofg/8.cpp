#include "sndfile.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_seek
    sf_count_t result = sf_seek(sndfile, offset, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_seek to sf_writef_float
    int ret_sf_close_rvjol = sf_close(NULL);
    if (ret_sf_close_rvjol < 0){
    	return 0;
    }

    sf_count_t ret_sf_writef_float_kidbt = sf_writef_float(sndfile, (const float *)&ret_sf_close_rvjol, result);
    if (ret_sf_writef_float_kidbt < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}