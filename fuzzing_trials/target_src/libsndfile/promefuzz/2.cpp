// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_open at sndfile.c:348:1 in sndfile.h
// sf_set_string at sndfile.c:1631:1 in sndfile.h
// sf_command at sndfile.c:995:1 in sndfile.h
// sf_error at sndfile.c:591:1 in sndfile.h
// sf_close at sndfile.c:517:1 in sndfile.h
// sf_open_fd at sndfile.c:440:1 in sndfile.h
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
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO) + 10) {
        return 0; // Ensure there's enough data for SF_INFO and more
    }

    writeDummyFile(Data, Size);

    SF_INFO sfinfo;
    sfinfo.frames = static_cast<sf_count_t>(Data[0]);
    sfinfo.samplerate = static_cast<int>(Data[1]);

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_READ, &sfinfo);
    if (sndfile) {
        int str_type = Data[2];
        const char *str = reinterpret_cast<const char *>(&Data[3]);
        sf_set_string(sndfile, str_type, str);

        int command = Data[4];
        void *cmd_data = nullptr;
        int datasize = static_cast<int>(Data[5]);
        sf_command(sndfile, command, cmd_data, datasize);

        sf_error(sndfile);

        sf_close(sndfile);
    }

    int fd = open("./dummy_file", O_RDONLY);
    if (fd != -1) {
        SNDFILE *sndfile_fd = sf_open_fd(fd, SFM_READ, &sfinfo, 1);
        if (sndfile_fd) {
            sf_close(sndfile_fd);
        } else {
            close(fd);
        }
    }

    return 0;
}