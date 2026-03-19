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

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
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
        int ret_sf_perror_ygwqz = sf_perror(sndfile);
        if (ret_sf_perror_ygwqz < 0){
        	return 0;
        }
        int ret_sf_error_liudc = sf_error(sndfile);
        if (ret_sf_error_liudc < 0){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_read_short
        int ret_sf_perror_exfhp = sf_perror(sndfile);
        if (ret_sf_perror_exfhp < 0){
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_perror to sf_writef_int
        int ret_sf_current_byterate_fzbly = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_fzbly < 0){
        	return 0;
        }


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_writef_int with sf_write_int
        sf_count_t ret_sf_writef_int_kvwko = sf_write_int(sndfile, &ret_sf_current_byterate_fzbly, (int64_t)ret_sf_perror_exfhp);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_sf_writef_int_kvwko < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_sf_current_byterate_eofxk = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_eofxk < 0){
        	return 0;
        }

        sf_count_t ret_sf_read_short_tpypk = sf_read_short(sndfile, (short *)&ret_sf_error_ctxnw, (int64_t )ret_sf_current_byterate_eofxk);
        if (ret_sf_read_short_tpypk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_read_short_ipfcy = sf_read_short(sndfile, (short *)&ret_sf_write_double_pkdai, (int64_t )ret_sf_error_liudc);
        if (ret_sf_read_short_ipfcy < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_short to sf_set_string
        int ret_sf_format_check_lqeds = sf_format_check(&sfinfo);
        if (ret_sf_format_check_lqeds < 0){
        	return 0;
        }
        const char oahhdugl[1024] = "khroq";

        int ret_sf_set_string_gjoqi = sf_set_string(sndfile, ret_sf_format_check_lqeds, oahhdugl);
        if (ret_sf_set_string_gjoqi < 0){
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_write_short
        sf_write_sync(sndfile);

        sf_count_t ret_sf_write_short_etayn = sf_write_short(sndfile, (const short *)&ret_sf_error_liudc, Size);
        if (ret_sf_write_short_etayn < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_perror with sf_close
        int ret_sf_perror_wrbtq = sf_close(NULL);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


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

    close(fd);
    return 0;
}