// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_write_float at sndfile.c:2463:1 in sndfile.h
// sf_readf_double at sndfile.c:2127:1 in sndfile.h
// sf_read_double at sndfile.c:2072:1 in sndfile.h
// sf_write_double at sndfile.c:2575:1 in sndfile.h
// sf_writef_double at sndfile.c:2632:1 in sndfile.h
// sf_write_int at sndfile.c:2351:1 in sndfile.h
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
#include <sndfile.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char *>(Data), Size);
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) + sizeof(double) + sizeof(int)) {
        return 0;
    }

    writeDummyFile(Data, Size);

    SF_INFO sfinfo = {0};
    sfinfo.frames = 1;
    sfinfo.samplerate = 44100;
    sfinfo.channels = 1;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    const float *floatData = reinterpret_cast<const float *>(Data);
    const double *doubleData = reinterpret_cast<const double *>(Data);
    const int *intData = reinterpret_cast<const int *>(Data);

    sf_write_float(sndfile, floatData, Size / sizeof(float));
    sf_readf_double(sndfile, const_cast<double *>(doubleData), Size / sizeof(double));
    sf_read_double(sndfile, const_cast<double *>(doubleData), Size / sizeof(double));
    sf_write_double(sndfile, doubleData, Size / sizeof(double));
    sf_writef_double(sndfile, doubleData, Size / sizeof(double));
    sf_write_int(sndfile, intData, Size / sizeof(int));

    sf_close(sndfile);
    return 0;
}