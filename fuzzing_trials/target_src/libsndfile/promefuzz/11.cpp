// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_write_raw at sndfile.c:2180:1 in sndfile.h
// sf_readf_short at sndfile.c:1803:1 in sndfile.h
// sf_write_sync at sndfile.c:526:1 in sndfile.h
// sf_writef_int at sndfile.c:2408:1 in sndfile.h
// sf_writef_short at sndfile.c:2296:1 in sndfile.h
// sf_write_short at sndfile.c:2239:1 in sndfile.h
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file for testing
    const char *dummyFileName = "./dummy_file";
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *sndfile = sf_open(dummyFileName, SFM_RDWR, &sfinfo);
    if (!sndfile) {
        std::cerr << "Failed to open dummy file." << std::endl;
        return 0;
    }

    // Allocate buffers
    short *shortBuffer = new short[Size / sizeof(short)];
    int *intBuffer = new int[Size / sizeof(int)];

    // Copy data to buffers
    memcpy(shortBuffer, Data, Size < sizeof(short) ? 0 : Size - (Size % sizeof(short)));
    memcpy(intBuffer, Data, Size < sizeof(int) ? 0 : Size - (Size % sizeof(int)));

    // Fuzz sf_write_raw
    sf_write_raw(sndfile, Data, Size);

    // Fuzz sf_readf_short
    sf_readf_short(sndfile, shortBuffer, Size / sizeof(short));

    // Fuzz sf_write_sync
    sf_write_sync(sndfile);

    // Fuzz sf_writef_int
    sf_writef_int(sndfile, intBuffer, Size / sizeof(int));

    // Fuzz sf_writef_short
    sf_writef_short(sndfile, shortBuffer, Size / sizeof(short));

    // Fuzz sf_write_short
    sf_write_short(sndfile, shortBuffer, Size / sizeof(short));

    // Cleanup
    sf_close(sndfile);
    delete[] shortBuffer;
    delete[] intBuffer;

    return 0;
}