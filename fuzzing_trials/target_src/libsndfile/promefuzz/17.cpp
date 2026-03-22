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
extern "C" {
#include <sndfile.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) {
        return 0;
    }

    write_dummy_file(Data, Size);

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(sfinfo));

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    float buffer[1024];
    int intBuffer[1024];
    double doubleBuffer[1024];

    sf_count_t frames = Size / sizeof(float);
    sf_count_t items = Size / sizeof(float);

    // Fuzz sf_readf_float
    sf_readf_float(sndfile, buffer, frames);

    // Fuzz sf_write_float
    sf_write_float(sndfile, buffer, items);

    // Fuzz sf_read_float
    sf_read_float(sndfile, buffer, items);

    // Fuzz sf_read_int
    sf_read_int(sndfile, intBuffer, items);

    // Fuzz sf_writef_float
    sf_writef_float(sndfile, buffer, frames);

    // Fuzz sf_read_double
    sf_read_double(sndfile, doubleBuffer, items);

    sf_close(sndfile);

    return 0;
}