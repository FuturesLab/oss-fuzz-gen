#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "sndfile.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(SF_INFO)) {
        return 0;
    }

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 2;
    sfinfo.samplerate = 44100;

    write_dummy_file(Data, Size);

    SNDFILE *sndfile = sf_open("./dummy_file", SFM_RDWR, &sfinfo);
    if (!sndfile) {
        return 0;
    }

    // Test sf_write_raw
    sf_count_t bytes_written = sf_write_raw(sndfile, Data, Size);

    // Test sf_seek
    sf_count_t seek_result = sf_seek(sndfile, 0, SEEK_SET);

    // Prepare buffer for sf_read_double
    double *buffer = new double[Size / sizeof(double)];
    sf_count_t items_read = sf_read_double(sndfile, buffer, Size / sizeof(double));
    delete[] buffer;

    // Test sf_format_check
    int format_check = sf_format_check(&sfinfo);

    // Test sf_current_byterate
    int byterate = sf_current_byterate(sndfile);

    // Prepare buffer for sf_read_raw
    void *raw_buffer = malloc(Size);
    sf_count_t raw_bytes_read = sf_read_raw(sndfile, raw_buffer, Size);
    free(raw_buffer);

    sf_close(sndfile);

    return 0;
}