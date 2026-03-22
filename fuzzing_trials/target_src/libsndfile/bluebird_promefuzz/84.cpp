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

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
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
    char njnineww[1024] = "prlkq";
    SNDFILE *sndfile = sf_open_virtual(&sfvirtual, mode, &sfinfo, njnineww);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (sndfile) {
        // Fuzz sf_readf_double
        double buffer[1024];

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_readf_double with sf_read_double
        sf_read_double(sndfile, buffer, 1024);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Fuzz sf_seek

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_readf_double to sf_write_double

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_double to sf_readf_short
        int ret_sf_current_byterate_brkpe = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_brkpe < 0){
        	return 0;
        }

        sf_count_t ret_sf_readf_short_vlmzn = sf_readf_short(sndfile, (short *)buffer, -1);
        if (ret_sf_readf_short_vlmzn < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_write_sync(sndfile);
        int ret_sf_error_ctxnw = sf_error(sndfile);
        if (ret_sf_error_ctxnw < 0){
        	return 0;
        }

        sf_count_t ret_sf_write_double_pkdai = sf_write_double(sndfile, buffer, (int64_t )ret_sf_error_ctxnw);
        if (ret_sf_write_double_pkdai < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_double to sf_read_short
        int ret_sf_perror_ygwqz = sf_perror(sndfile);
        if (ret_sf_perror_ygwqz < 0){
        	return 0;
        }
        int ret_sf_error_liudc = sf_error(sndfile);
        if (ret_sf_error_liudc < 0){
        	return 0;
        }

        sf_count_t ret_sf_read_short_ipfcy = sf_read_short(sndfile, (short *)&ret_sf_write_double_pkdai, (int64_t )ret_sf_error_liudc);
        if (ret_sf_read_short_ipfcy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_seek
        sf_seek(sndfile, 0, -1);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // Fuzz sf_write_int
        int int_buffer[1024];
        sf_write_int(sndfile, int_buffer, 1024);

        // Check for errors
        sf_error(sndfile);

        // Close the file

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_readf_short
        int ret_sf_perror_wrbtq = sf_perror(NULL);
        if (ret_sf_perror_wrbtq < 0){
        	return 0;
        }

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_current_byterate with sf_perror
        int ret_sf_current_byterate_dakpb = sf_perror(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_sf_current_byterate_dakpb < 0){
        	return 0;
        }

        sf_count_t ret_sf_readf_short_wqkwq = sf_readf_short(sndfile, (short *)&ret_sf_perror_wrbtq, (int64_t )ret_sf_current_byterate_dakpb);
        if (ret_sf_readf_short_wqkwq < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_close(sndfile);
    }

    close(fd);
    return 0;
}