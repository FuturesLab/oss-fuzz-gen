#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "sndfile.h"
}

#include <cstdint>
#include <cstring>
#include <cstdio>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    // Open the dummy file using libsndfile
    SF_INFO sfinfo;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_open
    SNDFILE *sndfile = sf_open("./dummy_file", Size, &sfinfo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Test sf_perror

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_readf_short
    int ret_sf_format_check_iumvo = sf_format_check(&sfinfo);
    if (ret_sf_format_check_iumvo < 0){
    	return 0;
    }
    int ret_sf_perror_dgofy = sf_perror(sndfile);
    if (ret_sf_perror_dgofy < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_short_yedlf = sf_readf_short(sndfile, (short *)&ret_sf_format_check_iumvo, (int64_t )ret_sf_perror_dgofy);
    if (ret_sf_readf_short_yedlf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_perror(sndfile);

    // Test sf_command with different commands
    int command = Data[0] % 5; // choose a command based on input data
    char data[256] = {};
    sf_command(sndfile, command, data, sizeof(data));

    // Test sf_error_str
    char errorStr[256];

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_error_str
    sf_error_str(sndfile, NULL, sizeof(errorStr));
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Test sf_strerror
    const char *strError = sf_strerror(sndfile);

    // Test sf_error_number with different error numbers
    int errnum = Data[0] % 10; // choose an error number based on input data
    const char *errorNumberStr = sf_error_number(errnum);

    // Test sf_get_string with different string types
    int strType = Data[0] % 3; // choose a string type based on input data
    const char *getString = sf_get_string(sndfile, strType);

    // Clean up
    if (sndfile) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_close with sf_perror
        sf_perror(sndfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }  return 0;
}