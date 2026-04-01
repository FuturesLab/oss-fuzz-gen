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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_seek

    sf_count_t ret_sf_seek_kmnlv = sf_seek(sndfile, 1, 1);
    if (ret_sf_seek_kmnlv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_set_string_gmfzc = sf_set_string(sndfile, 64, (const char *)"w");
    if (ret_sf_set_string_gmfzc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t short_read = sf_read_short(sndfile, short_buffer, 1024);

    // Read int samples
    sf_count_t int_read = sf_read_int(sndfile, int_buffer, 1024);

    // Read double samples
    sf_count_t double_read = sf_read_double(sndfile, double_buffer, 1024);

    // Close the sound file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_double to sf_read_short

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_double to sf_writef_double
    const char* ret_sf_strerror_xzqgp = sf_strerror(sndfile);
    if (ret_sf_strerror_xzqgp == NULL){
    	return 0;
    }
    int ret_sf_error_kxmai = sf_error(sndfile);
    if (ret_sf_error_kxmai < 0){
    	return 0;
    }

    sf_count_t ret_sf_writef_double_vgfsb = sf_writef_double(sndfile, (const double *)&ret_sf_error_kxmai, double_read);
    if (ret_sf_writef_double_vgfsb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const char* ret_sf_strerror_qyocf = sf_strerror(sndfile);
    if (ret_sf_strerror_qyocf == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_read_short with sf_readf_short
    sf_count_t ret_sf_read_short_dzjgc = sf_readf_short(sndfile, (short *)double_buffer, double_read);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_sf_read_short_dzjgc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int close_result = sf_close(sndfile);
    if (close_result != 0) {
        std::cerr << "Failed to close sound file." << std::endl;
    }

    return 0;
}