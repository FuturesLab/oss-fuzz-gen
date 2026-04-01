// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open_fd at sndfile.c:440:1 in sndfile.h
// sf_readf_int at sndfile.c:1911:1 in sndfile.h
// sf_read_int at sndfile.c:1856:1 in sndfile.h
// sf_error at sndfile.c:591:1 in sndfile.h
// sf_writef_int at sndfile.c:2408:1 in sndfile.h
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
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) {
        return 0;
    }

    write_dummy_file(Data, Size);

    SF_INFO sfinfo;
    sfinfo.frames = 0;
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.sections = 1;
    sfinfo.seekable = 1;

    int fd = open("./dummy_file", O_RDWR);
    if (fd < 0) {
        return 0;
    }

    SNDFILE *sndfile = sf_open_fd(fd, SFM_READ, &sfinfo, 1);
    if (!sndfile) {
        close(fd);
        return 0;
    }

    int buffer[1024];
    sf_count_t frames = Size / sizeof(int);

    // Fuzz sf_readf_int
    sf_readf_int(sndfile, buffer, frames);

    // Fuzz sf_read_int
    sf_read_int(sndfile, buffer, frames * sfinfo.channels);

    // Fuzz sf_error
    sf_error(sndfile);

    // Fuzz sf_writef_int
    sf_writef_int(sndfile, buffer, frames);

    // Fuzz sf_write_int
    sf_write_int(sndfile, buffer, frames * sfinfo.channels);

    sf_close(sndfile);

    return 0;
}