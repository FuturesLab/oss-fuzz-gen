#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_open
    SNDFILE *sndfile = sf_open(tmpl, size, &sfinfo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_current_byterate

    int ret_sf_current_byterate_pplhf = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_pplhf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_read_int_fseqh = sf_read_int(sndfile, &ret_sf_error_xjdvl, 1);
    if (ret_sf_read_int_fseqh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_int to sf_writef_int
    const int ozdzrbdd = 1;

    sf_count_t ret_sf_writef_int_ekrum = sf_writef_int(NULL, &ozdzrbdd, ret_sf_read_int_fseqh);
    if (ret_sf_writef_int_ekrum < 0){
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