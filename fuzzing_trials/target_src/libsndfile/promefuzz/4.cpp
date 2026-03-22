// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_perror at sndfile.c:609:1 in sndfile.h
// sf_command at sndfile.c:995:1 in sndfile.h
// sf_error_str at sndfile.c:630:1 in sndfile.h
// sf_strerror at sndfile.c:563:1 in sndfile.h
// sf_error_number at sndfile.c:541:1 in sndfile.h
// sf_get_string at sndfile.c:1619:1 in sndfile.h
// sf_close at sndfile.c:517:1 in sndfile.h
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
#include <sndfile.h>
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

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    // Open the dummy file using libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);

    // Test sf_perror
    sf_perror(sndfile);

    // Test sf_command with different commands
    int command = Data[0] % 5; // choose a command based on input data
    char data[256] = {};
    sf_command(sndfile, command, data, sizeof(data));

    // Test sf_error_str
    char errorStr[256];
    sf_error_str(sndfile, errorStr, sizeof(errorStr));

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
        sf_close(sndfile);
    }

    return 0;
}