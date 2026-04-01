#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Temporary file creation
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
    close(fd);

    // Open the file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        remove(tmpl);
        return 0;
    }

    // Initialize SF_CHUNK_INFO
    SF_CHUNK_INFO chunk_info;

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_read_int
    int ret_sf_error_xjdvl = sf_error(sndfile);
    if (ret_sf_error_xjdvl < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_get_string

    const char* ret_sf_get_string_azuhw = sf_get_string(NULL, ret_sf_error_xjdvl);
    if (ret_sf_get_string_azuhw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_close_shmmt = sf_close(NULL);
    if (ret_sf_close_shmmt < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_int_wwzgz = sf_read_int(sndfile, &ret_sf_error_xjdvl, (int64_t )ret_sf_close_shmmt);
    if (ret_sf_read_int_wwzgz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    memset(chunk_info.id, 0, sizeof(chunk_info.id));  // Proper initialization
    chunk_info.datalen = 0;
    chunk_info.data = NULL;

    // Call the function-under-test
    SF_CHUNK_ITERATOR *iterator = sf_get_chunk_iterator(sndfile, &chunk_info);

    // Clean up
    if (iterator != NULL) {
        sf_next_chunk_iterator(iterator);  // Use the correct function
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_get_chunk_iterator to sf_readf_short
    int ret_sf_error_fihrt = sf_error(sndfile);
    if (ret_sf_error_fihrt < 0){
    	return 0;
    }
    int ret_sf_perror_hgptc = sf_perror(sndfile);
    if (ret_sf_perror_hgptc < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_short_hsyab = sf_readf_short(sndfile, (short *)&ret_sf_error_fihrt, (int64_t )ret_sf_perror_hgptc);
    if (ret_sf_readf_short_hsyab < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);
    remove(tmpl);

    return 0;
}