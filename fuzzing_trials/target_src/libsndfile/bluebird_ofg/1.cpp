#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a buffer to read floats
    sf_count_t num_frames = 1024; // Number of frames to read

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_write_short

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_error_str
    int ret_sf_perror_gnxga = sf_perror(NULL);
    if (ret_sf_perror_gnxga < 0){
    	return 0;
    }

    int ret_sf_error_str_hqgtx = sf_error_str(sndfile, (char *)"r", (size_t )ret_sf_perror_gnxga);
    if (ret_sf_error_str_hqgtx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error_str to sf_read_float
    sf_write_sync(sndfile);
    int ret_sf_perror_pdyll = sf_perror(sndfile);
    if (ret_sf_perror_pdyll < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_float_tsvri = sf_read_float(sndfile, (float *)&ret_sf_error_str_hqgtx, (int64_t )ret_sf_perror_pdyll);
    if (ret_sf_read_float_tsvri < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_current_byterate_tkhbz = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_tkhbz < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_current_byterate to sf_strerror

    const char* ret_sf_strerror_xwbgu = sf_strerror(sndfile);
    if (ret_sf_strerror_xwbgu == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_write_short_xuagt = sf_write_short(sndfile, (const short *)&ret_sf_current_byterate_tkhbz, size);
    if (ret_sf_write_short_xuagt < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    float *buffer = (float *)malloc(num_frames * sfinfo.channels * sizeof(float));
    if (buffer == NULL) {
        sf_close(sndfile);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_read_float(sndfile, buffer, num_frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}