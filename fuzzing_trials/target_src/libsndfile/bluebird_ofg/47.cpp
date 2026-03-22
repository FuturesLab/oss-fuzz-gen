#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_read_short
    const char* ret_sf_strerror_afpje = sf_strerror(sndfile);
    if (ret_sf_strerror_afpje == NULL){
    	return 0;
    }
    int ret_sf_perror_begtl = sf_perror(NULL);
    if (ret_sf_perror_begtl < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_short_ofzid = sf_read_short(sndfile, (short *)&ret_sf_perror_begtl, (int64_t )ret_sf_error_xjdvl);
    if (ret_sf_read_short_ofzid < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_short to sf_read_int
    sf_write_sync(sndfile);

    sf_count_t ret_sf_read_int_mlwvm = sf_read_int(sndfile, (int *)&ret_sf_read_short_ofzid, ret_sf_read_short_ofzid);
    if (ret_sf_read_int_mlwvm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_read_int_fseqh = sf_read_int(sndfile, &ret_sf_error_xjdvl, 1);
    if (ret_sf_read_int_fseqh < 0){
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
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}