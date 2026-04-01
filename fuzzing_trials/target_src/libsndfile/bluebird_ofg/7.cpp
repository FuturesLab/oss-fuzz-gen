#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_format_check to sf_read_double

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_current_byterate with sf_perror
    int ret_sf_current_byterate_zltxk = sf_perror(sndfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_sf_current_byterate_zltxk < 0){
    	return 0;
    }
    int ret_sf_perror_hnuhp = sf_perror(NULL);
    if (ret_sf_perror_hnuhp < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_double_mccur = sf_read_double(sndfile, (double *)&ret_sf_format_check_cwnme, (int64_t )ret_sf_perror_hnuhp);
    if (ret_sf_read_double_mccur < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_read_float_uhnrh = sf_read_float(sndfile, (float *)&ret_sf_error_jppng, (int64_t )ret_sf_format_check_cwnme);
    if (ret_sf_read_float_uhnrh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_float to sf_write_raw
    int ret_sf_current_byterate_xoeyb = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_xoeyb < 0){
    	return 0;
    }

    sf_count_t ret_sf_write_raw_zbbeu = sf_write_raw(sndfile, (const void *)sndfile, size);
    if (ret_sf_write_raw_zbbeu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_writef_int_sepwc = sf_writef_int(sndfile, &jzwmjgzo, 1);
    if (ret_sf_writef_int_sepwc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);
    remove(tmpl);

    return 0;
}