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

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_readf_double with sf_read_double
        sf_read_double(sndfile, buffer, 1024);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Fuzz sf_seek
        sf_seek(sndfile, 0, SEEK_SET);

        // Fuzz sf_write_int
        int int_buffer[1024];

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_seek to sf_command
        int ret_sf_close_dwvai = sf_close(NULL);
        if (ret_sf_close_dwvai < 0){
        	return 0;
        }
        int ret_sf_current_byterate_tdwbx = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_tdwbx < 0){
        	return 0;
        }

        int ret_sf_command_njlsr = sf_command(sndfile, ret_sf_close_dwvai, (void *)sndfile, Size);
        if (ret_sf_command_njlsr < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_write_int(sndfile, int_buffer, 1024);

        // Check for errors

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_error with sf_current_byterate
        sf_current_byterate(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Close the file

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_current_byterate to sf_writef_float
        const float duspjyza = 0;

        sf_count_t ret_sf_writef_float_sjnae = sf_writef_float(sndfile, &duspjyza, 1);
        if (ret_sf_writef_float_sjnae < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_close(sndfile);
    }

    close(fd);
    return 0;
}