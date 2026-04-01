// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open_fd at sndfile.c:440:1 in sndfile.h
// sf_write_float at sndfile.c:2463:1 in sndfile.h
// sf_writef_double at sndfile.c:2632:1 in sndfile.h
// sf_write_int at sndfile.c:2351:1 in sndfile.h
// sf_command at sndfile.c:995:1 in sndfile.h
// sf_write_sync at sndfile.c:526:1 in sndfile.h
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
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO)) return 0;

    // Create a dummy file to be used by libsndfile
    const char *dummyFileName = "./dummy_file";
    int fd = open(dummyFileName, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return 0;

    // Prepare SF_INFO structure
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.frames = Size / sizeof(float);
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the dummy file with sf_open_fd
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (!sndfile) {
        close(fd);
        return 0;
    }

    // Allocate buffers for samples
    float *floatSamples = (float *)malloc(Size);
    size_t doubleSampleSize = (Size / sizeof(float)) * sizeof(double);
    size_t intSampleSize = (Size / sizeof(float)) * sizeof(int);
    double *doubleSamples = (double *)malloc(doubleSampleSize);
    int *intSamples = (int *)malloc(intSampleSize);

    if (floatSamples && doubleSamples && intSamples) {
        memcpy(floatSamples, Data, Size);

        // Fuzz sf_write_float
        sf_write_float(sndfile, floatSamples, sfinfo.frames * sfinfo.channels);

        // Fuzz sf_writef_double
        size_t doubleSamplesToCopy = Size / sizeof(float);
        if (doubleSampleSize <= Size) {
            memcpy(doubleSamples, floatSamples, doubleSamplesToCopy * sizeof(double));
        }
        sf_writef_double(sndfile, doubleSamples, sfinfo.frames);

        // Fuzz sf_write_int
        size_t intSamplesToCopy = Size / sizeof(float);
        if (intSampleSize <= Size) {
            memcpy(intSamples, floatSamples, intSamplesToCopy * sizeof(int));
        }
        sf_write_int(sndfile, intSamples, sfinfo.frames * sfinfo.channels);

        // Fuzz sf_command
        int command = SF_STR_TITLE;
        char title[256] = "Fuzzing Title";
        sf_command(sndfile, command, title, sizeof(title));

        // Fuzz sf_write_sync
        sf_write_sync(sndfile);
    }

    // Clean up
    sf_close(sndfile);
    free(floatSamples);
    free(doubleSamples);
    free(intSamples);
    close(fd);
    unlink(dummyFileName);

    return 0;
}