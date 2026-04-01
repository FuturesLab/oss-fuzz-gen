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

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_read_float
    int ret_sf_close_obkun = sf_close(NULL);
    if (ret_sf_close_obkun < 0){
    	return 0;
    }
    float pvqufsxh = 1;

    sf_count_t ret_sf_read_float_ijhoh = sf_read_float(sndfile, &pvqufsxh, (int64_t )ret_sf_close_obkun);
    if (ret_sf_read_float_ijhoh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t short_read = sf_read_short(sndfile, short_buffer, 1024);

    // Read int samples
    sf_count_t int_read = sf_read_int(sndfile, int_buffer, 1024);

    // Read double samples

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_int to sf_write_raw


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_write_raw
    sf_count_t ret_sf_write_raw_zpibw = sf_write_raw(sndfile, NULL, Size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_sf_write_raw_zpibw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t double_read = sf_read_double(sndfile, double_buffer, 1024);

    // Close the sound file
    int close_result = sf_close(sndfile);
    if (close_result != 0) {
        std::cerr << "Failed to close sound file." << std::endl;
    }

    return 0;
}