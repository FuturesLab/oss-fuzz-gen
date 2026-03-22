#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_format_check to sf_read_double
    int ret_sf_current_byterate_cbpjm = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_cbpjm < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_double_xuotv = sf_read_double(sndfile, (double *)&ret_sf_format_check_cwnme, 0);
    if (ret_sf_read_double_xuotv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_double to sf_open_fd
    int ret_sf_current_byterate_latox = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_latox < 0){
    	return 0;
    }
    int ret_sf_current_byterate_fltwa = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_fltwa < 0){
    	return 0;
    }
    SF_INFO qlncidmk;
    memset(&qlncidmk, 0, sizeof(qlncidmk));

    SNDFILE* ret_sf_open_fd_ullav = sf_open_fd((int )ret_sf_read_double_xuotv, ret_sf_current_byterate_latox, &qlncidmk, ret_sf_current_byterate_fltwa);
    if (ret_sf_open_fd_ullav == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_read_float_uhnrh = sf_read_float(sndfile, (float *)&ret_sf_error_jppng, (int64_t )ret_sf_format_check_cwnme);
    if (ret_sf_read_float_uhnrh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_writef_int_sepwc = sf_writef_int(sndfile, &jzwmjgzo, 1);
    if (ret_sf_writef_int_sepwc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_close(sndfile);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_next_chunk_iterator to sf_get_chunk_data
        SF_CHUNK_INFO xlqjavtv;
        memset(&xlqjavtv, 0, sizeof(xlqjavtv));

        int ret_sf_get_chunk_data_convm = sf_get_chunk_data(iterator, &xlqjavtv);
        if (ret_sf_get_chunk_data_convm < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    remove(tmpl);

    return 0;
}