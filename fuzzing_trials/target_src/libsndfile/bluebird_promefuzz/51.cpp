#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "sndfile.h"
#include <cstdint>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

static sf_count_t vio_get_filelen(void *user_data) {
    return lseek(*((int *)user_data), 0, SEEK_END);
}

static sf_count_t vio_seek(sf_count_t offset, int whence, void *user_data) {
    return lseek(*((int *)user_data), offset, whence);
}

static sf_count_t vio_read(void *ptr, sf_count_t count, void *user_data) {
    return read(*((int *)user_data), ptr, count);
}

static sf_count_t vio_write(const void *ptr, sf_count_t count, void *user_data) {
    return write(*((int *)user_data), ptr, count);
}

static sf_count_t vio_tell(void *user_data) {
    return lseek(*((int *)user_data), 0, SEEK_CUR);
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO) + sizeof(int)) {
        return 0;
    }

    // Prepare SF_INFO structure
    SF_INFO sfinfo;
    memcpy(&sfinfo, Data, sizeof(SF_INFO));
    Data += sizeof(SF_INFO);
    Size -= sizeof(SF_INFO);

    int mode = *(int *)Data;
    Data += sizeof(int);
    Size -= sizeof(int);

    // Prepare dummy file
    const char *filename = "./dummy_file";
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        return 0;
    }

    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);

    // Initialize SF_VIRTUAL_IO
    SF_VIRTUAL_IO sfvirtual;
    sfvirtual.get_filelen = vio_get_filelen;
    sfvirtual.seek = vio_seek;
    sfvirtual.read = vio_read;
    sfvirtual.write = vio_write;
    sfvirtual.tell = vio_tell;

    // Open virtual file
    SNDFILE *sndfile = sf_open_virtual(&sfvirtual, mode, &sfinfo, &fd);
    if (sndfile) {
        // Fuzz sf_readf_double
        double buffer[1024];

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_readf_double
        sf_readf_double(sndfile, buffer, -1);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // Fuzz sf_seek
        sf_seek(sndfile, 0, SEEK_SET);

        // Fuzz sf_write_int
        int int_buffer[1024];

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_seek to sf_set_string

        int ret_sf_set_string_uiaag = sf_set_string(sndfile, Size, (const char *)"w");
        if (ret_sf_set_string_uiaag < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_write_int(sndfile, int_buffer, 1024);

        // Check for errors

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_error with sf_current_byterate

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_int to sf_set_string

        int ret_sf_set_string_unmhk = sf_set_string(sndfile, Size, (const char *)"r");
        if (ret_sf_set_string_unmhk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_current_byterate(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Close the file

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_current_byterate to sf_writef_int
        int ret_sf_error_xrzqy = sf_error(sndfile);
        if (ret_sf_error_xrzqy < 0){
        	return 0;
        }
        int ret_sf_error_cvird = sf_error(sndfile);
        if (ret_sf_error_cvird < 0){
        	return 0;
        }

        sf_count_t ret_sf_writef_int_nsian = sf_writef_int(sndfile, &ret_sf_error_xrzqy, (int64_t )ret_sf_error_cvird);
        if (ret_sf_writef_int_nsian < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_close(sndfile);
    }

    close(fd);
    return 0;
}