// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_readf_float at sndfile.c:2019:1 in sndfile.h
// sf_write_float at sndfile.c:2463:1 in sndfile.h
// sf_read_float at sndfile.c:1964:1 in sndfile.h
// sf_read_int at sndfile.c:1856:1 in sndfile.h
// sf_writef_float at sndfile.c:2520:1 in sndfile.h
// sf_read_double at sndfile.c:2072:1 in sndfile.h
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
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO)) {
        return 0; // Not enough data to proceed
    }

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    // Create a dummy file for testing
    const char *dummyFile = "./dummy_file";
    SF_VIRTUAL_IO vio;
    memset(&vio, 0, sizeof(SF_VIRTUAL_IO));

    SNDFILE *sndfile = sf_open(dummyFile, SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0; // Could not open file
    }

    // Allocate buffers
    float *floatBuffer = new float[Size / sizeof(float)];
    int *intBuffer = new int[Size / sizeof(int)];
    double *doubleBuffer = new double[Size / sizeof(double)];

    // Read and write operations
    sf_count_t frames = Size / sizeof(float);
    sf_count_t samples = Size / sizeof(int);

    // sf_readf_float
    sf_readf_float(sndfile, floatBuffer, frames);

    // sf_write_float
    sf_write_float(sndfile, floatBuffer, samples);

    // sf_read_float
    sf_read_float(sndfile, floatBuffer, samples);

    // sf_read_int
    sf_read_int(sndfile, intBuffer, samples);

    // sf_writef_float
    sf_writef_float(sndfile, floatBuffer, frames);

    // sf_read_double
    sf_read_double(sndfile, doubleBuffer, samples);

    // Cleanup
    delete[] floatBuffer;
    delete[] intBuffer;
    delete[] doubleBuffer;
    sf_close(sndfile);

    return 0;
}