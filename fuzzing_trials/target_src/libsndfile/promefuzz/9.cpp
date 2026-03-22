// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_write_raw at sndfile.c:2180:1 in sndfile.h
// sf_close at sndfile.c:517:1 in sndfile.h
// sf_write_sync at sndfile.c:526:1 in sndfile.h
// sf_writef_short at sndfile.c:2296:1 in sndfile.h
// sf_close at sndfile.c:517:1 in sndfile.h
// sf_close at sndfile.c:517:1 in sndfile.h
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <sndfile.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    writeDummyFile(Data, Size);

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_WRITE, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    // Ensure the number of frames does not exceed the available data
    sf_count_t numFrames = Size / (sfinfo.channels * sizeof(short));

    // Test sf_write_raw
    sf_count_t bytesWritten = sf_write_raw(sndfile, Data, Size);
    if (bytesWritten < 0) {
        sf_close(sndfile);
        return 0;
    }

    // Test sf_write_sync
    sf_write_sync(sndfile);

    // Test sf_writef_short
    if (numFrames > 0) {
        const short *shortData = reinterpret_cast<const short *>(Data);
        sf_count_t framesWrittenShort = sf_writef_short(sndfile, shortData, numFrames);
        if (framesWrittenShort < 0) {
            sf_close(sndfile);
            return 0;
        }
    }

    sf_close(sndfile);
    return 0;
}