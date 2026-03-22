#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_float to sf_command
    int ret_sf_current_byterate_cyvjr = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_cyvjr < 0){
    	return 0;
    }

    int ret_sf_command_woyyq = sf_command(sndfile, 64, NULL, ret_sf_current_byterate_cyvjr);
    if (ret_sf_command_woyyq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_writef_int_sepwc = sf_writef_int(sndfile, &jzwmjgzo, 1);
    if (ret_sf_writef_int_sepwc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_readf_int
    int ret_sf_perror_pmniq = sf_perror(NULL);
    if (ret_sf_perror_pmniq < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_int_lzwbq = sf_readf_int(sndfile, (int *)&ret_sf_writef_int_sepwc, (int64_t )ret_sf_perror_pmniq);
    if (ret_sf_readf_int_lzwbq < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    remove(tmpl);

    return 0;
}