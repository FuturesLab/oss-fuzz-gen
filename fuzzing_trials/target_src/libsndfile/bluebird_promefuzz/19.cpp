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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    SF_INFO sfinfo;
    std::memset(&sfinfo, 0, sizeof(SF_INFO));

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    // Buffers for reading samples
    short short_buffer[1024];
    int int_buffer[1024];
    double double_buffer[1024];

    // Read short samples

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_set_string
    int ret_sf_format_check_axgek = sf_format_check(&sfinfo);
    if (ret_sf_format_check_axgek < 0){
    	return 0;
    }

    int ret_sf_set_string_rrvjk = sf_set_string(sndfile, ret_sf_format_check_axgek, (const char *)Data);
    if (ret_sf_set_string_rrvjk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_set_string to sf_writef_double
    int ret_sf_perror_zbwcy = sf_perror(sndfile);
    if (ret_sf_perror_zbwcy < 0){
    	return 0;
    }
    int ret_sf_close_bbdsd = sf_close(NULL);
    if (ret_sf_close_bbdsd < 0){
    	return 0;
    }

    sf_count_t ret_sf_writef_double_faeqr = sf_writef_double(sndfile, (const double *)&ret_sf_close_bbdsd, (int64_t )ret_sf_set_string_rrvjk);
    if (ret_sf_writef_double_faeqr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t short_read = sf_read_short(sndfile, short_buffer, 1024);

    // Read int samples
    sf_count_t int_read = sf_read_int(sndfile, int_buffer, 1024);

    // Read double samples
    sf_count_t double_read = sf_read_double(sndfile, double_buffer, 1024);

    // Close the sound file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_double to sf_read_float
    const char* ret_sf_strerror_giniw = sf_strerror(sndfile);
    if (ret_sf_strerror_giniw == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_read_float with sf_readf_float
    sf_count_t ret_sf_read_float_dzgkj = sf_readf_float(sndfile, (float *)double_buffer, short_read);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_sf_read_float_dzgkj < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int close_result = sf_close(sndfile);
    if (close_result != 0) {
        std::cerr << "Failed to close sound file." << std::endl;
    }

    return 0;
}