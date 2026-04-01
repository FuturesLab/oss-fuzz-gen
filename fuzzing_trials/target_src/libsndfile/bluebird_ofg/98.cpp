#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
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
    memset(chunk_info.id, 0, sizeof(chunk_info.id));  // Proper initialization
    chunk_info.datalen = 0;
    chunk_info.data = NULL;

    // Call the function-under-test
    SF_CHUNK_ITERATOR *iterator = sf_get_chunk_iterator(sndfile, &chunk_info);

    // Clean up
    if (iterator != NULL) {
        sf_next_chunk_iterator(iterator);  // Use the correct function
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_get_chunk_iterator to sf_writef_int
    const int jzwmjgzo = 0;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_get_chunk_iterator to sf_read_float
    int ret_sf_error_jppng = sf_error(NULL);
    if (ret_sf_error_jppng < 0){
    	return 0;
    }
    int ret_sf_format_check_cwnme = sf_format_check(&sfinfo);
    if (ret_sf_format_check_cwnme < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_float_uhnrh = sf_read_float(sndfile, (float *)&ret_sf_error_jppng, (int64_t )ret_sf_format_check_cwnme);
    if (ret_sf_read_float_uhnrh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_writef_int
    const int pmxwmchu = 1;
    sf_count_t ret_sf_writef_int_sepwc = sf_writef_int(sndfile, &pmxwmchu, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_sf_writef_int_sepwc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);
    remove(tmpl);

    return 0;
}