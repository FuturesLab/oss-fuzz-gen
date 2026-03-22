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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    std::ofstream ofs("./dummy_file", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();
}

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    SF_INFO sfinfo;
    std::memset(&sfinfo, 0, sizeof(SF_INFO));


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_open
    SNDFILE *sndfile = sf_open("./dummy_file", Size, &sfinfo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!sndfile) {
        return 0;
    }

    // Buffers for reading samples
    short short_buffer[1024];
    int int_buffer[1024];
    double double_buffer[1024];

    // Read short samples

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_read_short
    sf_count_t short_read = sf_read_short(sndfile, short_buffer, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Read int samples

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_short to sf_command
    int ret_sf_close_urzdh = sf_close(sndfile);
    if (ret_sf_close_urzdh < 0){
    	return 0;
    }
    const char* ret_sf_strerror_lldia = sf_strerror(sndfile);
    if (ret_sf_strerror_lldia == NULL){
    	return 0;
    }
    int ret_sf_current_byterate_phfvw = sf_current_byterate(NULL);
    if (ret_sf_current_byterate_phfvw < 0){
    	return 0;
    }

    int ret_sf_command_uybxh = sf_command(sndfile, (int )short_read, (void *)sndfile, ret_sf_current_byterate_phfvw);
    if (ret_sf_command_uybxh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t int_read = sf_read_int(sndfile, int_buffer, 1024);

    // Read double samples
    sf_count_t double_read = sf_read_double(sndfile, double_buffer, 1024);

    // Close the sound file

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_close with sf_error
    int close_result = sf_error(sndfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (close_result != 0) {
        std::cerr << "Failed to close sound file." << std::endl;
    }

    return 0;
}