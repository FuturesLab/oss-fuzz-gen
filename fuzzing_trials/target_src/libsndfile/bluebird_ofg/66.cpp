#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // For write and close
#include <fcntl.h>   // For mkstemp
#include <stdio.h>   // For remove
#include <string.h>  // For memset

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_open_virtual
    int ret_sf_perror_ucwgx = sf_perror(sndfile);
    if (ret_sf_perror_ucwgx < 0){
    	return 0;
    }
    SF_CHUNK_ITERATOR* ret_sf_next_chunk_iterator_feekl = sf_next_chunk_iterator(NULL);
    if (ret_sf_next_chunk_iterator_feekl == NULL){
    	return 0;
    }

    SNDFILE* ret_sf_open_virtual_utots = sf_open_virtual(NULL, ret_sf_perror_ucwgx, &sfinfo, (void *)ret_sf_next_chunk_iterator_feekl);
    if (ret_sf_open_virtual_utots == NULL){
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