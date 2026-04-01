// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_readf_float at sndfile.c:2019:1 in sndfile.h
// sf_read_float at sndfile.c:1964:1 in sndfile.h
// sf_read_int at sndfile.c:1856:1 in sndfile.h
// sf_read_double at sndfile.c:2072:1 in sndfile.h
// sf_readf_short at sndfile.c:1803:1 in sndfile.h
// sf_read_short at sndfile.c:1748:1 in sndfile.h
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
#include <cstring>
#include <iostream>
#include <fstream>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    std::ofstream ofs("./dummy_file", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(Data), Size);
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;  // Ensure there is at least some data

    // Write the input data to a dummy file
    write_dummy_file(Data, Size);

    // Open the dummy file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);
    if (!sndfile) {
        return 0;  // If the file can't be opened, exit early
    }

    // Prepare buffers for reading
    sf_count_t frames = sfinfo.frames;
    float *float_buffer = new float[frames];
    int *int_buffer = new int[frames];
    double *double_buffer = new double[frames];
    short *short_buffer = new short[frames];

    // Fuzz sf_readf_float
    sf_readf_float(sndfile, float_buffer, frames);

    // Fuzz sf_read_float
    sf_read_float(sndfile, float_buffer, frames * sfinfo.channels);

    // Fuzz sf_read_int
    sf_read_int(sndfile, int_buffer, frames * sfinfo.channels);

    // Fuzz sf_read_double
    sf_read_double(sndfile, double_buffer, frames * sfinfo.channels);

    // Fuzz sf_readf_short
    sf_readf_short(sndfile, short_buffer, frames);

    // Fuzz sf_read_short
    sf_read_short(sndfile, short_buffer, frames * sfinfo.channels);

    // Cleanup
    delete[] float_buffer;
    delete[] int_buffer;
    delete[] double_buffer;
    delete[] short_buffer;
    sf_close(sndfile);

    return 0;
}