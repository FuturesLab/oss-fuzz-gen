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
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO) + 10) {
        return 0; // Ensure there's enough data for SF_INFO and more
    }

    writeDummyFile(Data, Size);

    SF_INFO sfinfo;
    sfinfo.frames = static_cast<sf_count_t>(Data[0]);
    sfinfo.samplerate = static_cast<int>(Data[1]);

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);
    if (sndfile) {
        int str_type = Data[2];
        const char *str = reinterpret_cast<const char *>(&Data[3]);
        sf_set_string(sndfile, str_type, str);

        int command = Data[4];
        void *cmd_data = nullptr;
        int datasize = static_cast<int>(Data[5]);
        sf_command(sndfile, command, cmd_data, datasize);

        sf_error(sndfile);

        sf_close(sndfile);
    }

    int fd = open("./dummy_file", O_RDONLY);
    if (fd != -1) {
        SNDFILE *sndfile_fd = sf_open_fd(fd, SFM_READ, &sfinfo, 1);
        if (sndfile_fd) {
            sf_close(sndfile_fd);
        } else {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open_fd to sf_perror

        int ret_sf_perror_llrjz = sf_perror(sndfile_fd);
        if (ret_sf_perror_llrjz < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_writef_double
            int ret_sf_perror_rompe = sf_perror(sndfile_fd);
            if (ret_sf_perror_rompe < 0){
            	return 0;
            }
            int ret_sf_perror_qymue = sf_perror(sndfile);
            if (ret_sf_perror_qymue < 0){
            	return 0;
            }

            sf_count_t ret_sf_writef_double_rmlvb = sf_writef_double(sndfile_fd, (const double *)&ret_sf_perror_rompe, (int64_t )ret_sf_perror_qymue);
            if (ret_sf_writef_double_rmlvb < 0){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            close(fd);
        }   }

    return 0;
}