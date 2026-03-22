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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_readf_double to sf_writef_int
        int ret_sf_error_tvhme = sf_error(sndfile);
        if (ret_sf_error_tvhme < 0){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_readf_float
        int ret_sf_perror_feijt = sf_perror(NULL);
        if (ret_sf_perror_feijt < 0){
        	return 0;
        }

        sf_count_t ret_sf_readf_float_yebck = sf_readf_float(sndfile, (float *)buffer, (int64_t )ret_sf_perror_feijt);
        if (ret_sf_readf_float_yebck < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_writef_int_ihntw = sf_writef_int(sndfile, (const int *)buffer, 1);
        if (ret_sf_writef_int_ihntw < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_seek(sndfile, 0, SEEK_SET);

        // Fuzz sf_write_int
        int int_buffer[1024];

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_seek to sf_writef_double
        int ret_sf_close_sqmhv = sf_close(NULL);
        if (ret_sf_close_sqmhv < 0){
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_write_float
        int ret_sf_perror_mrvep = sf_perror(sndfile);
        if (ret_sf_perror_mrvep < 0){
        	return 0;
        }
        int ret_sf_format_check_ibwem = sf_format_check(&sfinfo);
        if (ret_sf_format_check_ibwem < 0){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_format_check to sf_readf_short

        sf_count_t ret_sf_readf_short_xmebm = sf_readf_short(sndfile, (short *)&ret_sf_perror_mrvep, (int64_t )ret_sf_format_check_ibwem);
        if (ret_sf_readf_short_xmebm < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_write_float_jumhd = sf_write_float(sndfile, (const float *)&ret_sf_close_sqmhv, (int64_t )ret_sf_format_check_ibwem);
        if (ret_sf_write_float_jumhd < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_sf_perror_kfwxo = sf_perror(sndfile);
        if (ret_sf_perror_kfwxo < 0){
        	return 0;
        }

        sf_count_t ret_sf_writef_double_vffsk = sf_writef_double(sndfile, (const double *)&ret_sf_close_sqmhv, (int64_t )ret_sf_perror_kfwxo);
        if (ret_sf_writef_double_vffsk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_write_int(sndfile, int_buffer, 1024);

        // Check for errors

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_error with sf_current_byterate
        sf_current_byterate(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Close the file
        sf_close(sndfile);
    }

    close(fd);
    return 0;
}