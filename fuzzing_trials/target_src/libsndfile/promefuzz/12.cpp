// This fuzz driver is generated for library libsndfile, aiming to fuzz the following functions:
// sf_version_string at sndfile.c:981:1 in sndfile.h
// sf_format_check at sndfile.c:653:1 in sndfile.h
// sf_perror at sndfile.c:609:1 in sndfile.h
// sf_command at sndfile.c:995:1 in sndfile.h
// sf_error_number at sndfile.c:541:1 in sndfile.h
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
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void fuzz_sf_version_string() {
    const char* version = sf_version_string();
    if (version) {
        printf("Version: %s\n", version);
    }
}

static void fuzz_sf_format_check() {
    SF_INFO info;
    memset(&info, 0, sizeof(SF_INFO));
    info.samplerate = rand() % 96000;
    info.frames = rand() % 100000;
    int result = sf_format_check(&info);
    printf("Format check result: %d\n", result);
}

static void fuzz_sf_perror() {
    SNDFILE *sndfile = NULL;
    int result = sf_perror(sndfile);
    printf("Perror result: %d\n", result);
}

static void fuzz_sf_command() {
    SNDFILE *sndfile = NULL;
    int command = rand() % 10;
    int data = 0;
    int result = sf_command(sndfile, command, &data, sizeof(data));
    printf("Command result: %d\n", result);
}

static void fuzz_sf_error_number() {
    int errnum = rand() % 10;
    const char* error_str = sf_error_number(errnum);
    if (error_str) {
        printf("Error string: %s\n", error_str);
    }
}

static void fuzz_sf_open_fd() {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.samplerate = 44100;
    sfinfo.frames = 1000;

    SNDFILE *sndfile = sf_open_fd(fd, SFM_READ, &sfinfo, 1);
    if (sndfile) {
        sf_close(sndfile);
    }
    close(fd);
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    fuzz_sf_version_string();
    fuzz_sf_format_check();
    fuzz_sf_perror();
    fuzz_sf_command();
    fuzz_sf_error_number();
    fuzz_sf_open_fd();
    return 0;
}