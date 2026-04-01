#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    // Write the fuzz data to the temporary file
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare buffer for reading samples
    sf_count_t frames = 1024;  // Number of frames to read
    float *buffer = (float *)malloc(frames * sfinfo.channels * sizeof(float));
    if (buffer == NULL) {
        sf_close(sndfile);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_readf_double
        int ret_sf_current_byterate_dppra = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_dppra < 0){
        	return 0;
        }
        double zzuyaydy = -1;

        sf_count_t ret_sf_readf_double_flypw = sf_readf_double(sndfile, &zzuyaydy, (int64_t )ret_sf_current_byterate_dppra);
        if (ret_sf_readf_double_flypw < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_readf_float(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}