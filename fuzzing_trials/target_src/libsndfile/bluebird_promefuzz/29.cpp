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

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of sf_open_virtual
    char pphesdow[1024] = "afumv";
    SNDFILE *sndfile = sf_open_virtual(&sfvirtual, mode, &sfinfo, pphesdow);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_format_check to sf_read_float
        int ret_sf_error_majyu = sf_error(sndfile);
        if (ret_sf_error_majyu < 0){
        	return 0;
        }
        float deczopoa = -1;

        sf_count_t ret_sf_read_float_vganr = sf_read_float(sndfile, &deczopoa, (int64_t )ret_sf_format_check_ibwem);
        if (ret_sf_read_float_vganr < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_write_float_jumhd = sf_write_float(sndfile, (const float *)&ret_sf_close_sqmhv, (int64_t )ret_sf_format_check_ibwem);
        if (ret_sf_write_float_jumhd < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_float to sf_write_int
        int ret_sf_perror_qdwyr = sf_perror(sndfile);
        if (ret_sf_perror_qdwyr < 0){
        	return 0;
        }


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_write_int
        sf_count_t ret_sf_write_int_lkheb = sf_write_int(sndfile, NULL, (int64_t)ret_sf_perror_qdwyr);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_sf_write_int_lkheb < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_perror with sf_error
        int ret_sf_perror_kfwxo = sf_error(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_sf_perror_kfwxo < 0){
        	return 0;
        }


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_writef_double

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_read_short
        const char* ret_sf_strerror_gifjl = sf_strerror(sndfile);
        if (ret_sf_strerror_gifjl == NULL){
        	return 0;
        }

        sf_count_t ret_sf_read_short_ymorg = sf_read_short(sndfile, (short *)&ret_sf_perror_mrvep, (int64_t )ret_sf_error_majyu);
        if (ret_sf_read_short_ymorg < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_writef_double_vffsk = sf_writef_double(sndfile, (const double *)&ret_sf_close_sqmhv, -1);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_sf_writef_double_vffsk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_writef_double to sf_write_short
        const char* ret_sf_strerror_pocyh = sf_strerror(sndfile);
        if (ret_sf_strerror_pocyh == NULL){
        	return 0;
        }

        sf_count_t ret_sf_write_short_fvvym = sf_write_short(sndfile, (const short *)&ret_sf_writef_double_vffsk, (int64_t )ret_sf_format_check_ibwem);
        if (ret_sf_write_short_fvvym < 0){
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