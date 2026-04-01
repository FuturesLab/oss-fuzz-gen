#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
    const char *dummy_file = "./dummy_file";
    FILE *file = fopen(dummy_file, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file for reading and writing
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(dummy_file, SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    // Fuzz sf_write_raw

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_write_raw
    sf_count_t bytes_written = sf_write_raw(sndfile, Data, -1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz sf_seek
    sf_count_t frames = Size / (sfinfo.channels * sizeof(double)); // Estimate frames

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_raw to sf_error


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_raw to sf_write_double

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_raw to sf_command
    int ret_sf_error_svhxc = sf_error(sndfile);
    if (ret_sf_error_svhxc < 0){
    	return 0;
    }

    int ret_sf_command_tlvhd = sf_command(sndfile, Size, NULL, (int )bytes_written);
    if (ret_sf_command_tlvhd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_close_zeaxc = sf_close(NULL);
    if (ret_sf_close_zeaxc < 0){
    	return 0;
    }
    const double odvawqeq = 1;

    sf_count_t ret_sf_write_double_nulcy = sf_write_double(sndfile, &odvawqeq, (int64_t )ret_sf_close_zeaxc);
    if (ret_sf_write_double_nulcy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_error_qgnjr = sf_error(sndfile);
    if (ret_sf_error_qgnjr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_seek(sndfile, frames, SF_SEEK_SET);

    // Fuzz sf_read_double
    double *buffer = static_cast<double*>(malloc(Size * sizeof(double)));
    if (buffer) {
        sf_count_t items_read = sf_read_double(sndfile, buffer, frames);
        free(buffer);
    }

    // Fuzz sf_format_check
    int format_valid = sf_format_check(&sfinfo);

    // Fuzz sf_current_byterate
    int byterate = sf_current_byterate(sndfile);

    // Fuzz sf_read_raw
    void *raw_buffer = malloc(Size);
    if (raw_buffer) {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_read_raw
        sf_count_t bytes_read = sf_read_raw(sndfile, raw_buffer, 64);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        free(raw_buffer);
    }

    // Clean up
    sf_close(sndfile);
    remove(dummy_file);

    return 0;
}