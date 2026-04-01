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

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
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
        sf_readf_double(sndfile, buffer, 1024);

        // Fuzz sf_seek

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_readf_double to sf_write_double
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_double to sf_open
        const char tdubqvsg[1024] = "ilzzl";
        SF_INFO bdijbwuu;
        memset(&bdijbwuu, 0, sizeof(bdijbwuu));

        SNDFILE* ret_sf_open_mcntg = sf_open(tdubqvsg, (int )ret_sf_write_double_pkdai, &bdijbwuu);
        if (ret_sf_open_mcntg == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

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

        sf_seek(sndfile, 0, SEEK_SET);

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
        int ret_sf_current_byterate_dakpb = sf_current_byterate(sndfile);
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open_virtual to sf_open_fd
    int ret_sf_error_kbpjt = sf_error(NULL);
    if (ret_sf_error_kbpjt < 0){
    	return 0;
    }
    int ret_sf_error_augjy = sf_error(NULL);
    if (ret_sf_error_augjy < 0){
    	return 0;
    }

    SNDFILE* ret_sf_open_fd_gygrv = sf_open_fd(ret_sf_error_kbpjt, 64, &sfinfo, ret_sf_error_augjy);
    if (ret_sf_open_fd_gygrv == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    close(fd);
    return 0;
}