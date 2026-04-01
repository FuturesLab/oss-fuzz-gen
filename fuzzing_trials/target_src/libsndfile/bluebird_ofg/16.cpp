#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
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
    int ret_sf_format_check_sdsdm = sf_format_check(&sfinfo);
    if (ret_sf_format_check_sdsdm < 0){
    	return 0;
    }
    int ret_sf_error_xbubp = sf_error(sndfile);
    if (ret_sf_error_xbubp < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_short_zarkc = sf_readf_short(sndfile, (short *)&ret_sf_format_check_sdsdm, (int64_t )ret_sf_error_xbubp);
    if (ret_sf_readf_short_zarkc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_readf_short to sf_write_raw
    int ret_sf_perror_gqjof = sf_perror(sndfile);
    if (ret_sf_perror_gqjof < 0){
    	return 0;
    }

    sf_count_t ret_sf_write_raw_aqzbe = sf_write_raw(sndfile, (const void *)"w", ret_sf_readf_short_zarkc);
    if (ret_sf_write_raw_aqzbe < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);
    remove(tmpl);

    return 0;
}