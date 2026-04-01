// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzeof at gzlib.c:498:13 in zlib.h
// gzgetc_ at gzread.c:496:13 in zlib.h
// gzdirect at gzread.c:623:13 in zlib.h
// gzflush at gzwrite.c:603:13 in zlib.h
// gzclose_r at gzread.c:641:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

static void fuzz_gzdopen_gzeof_gzgetc_gzdirect_gzclose_r(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    // Create a dummy file with the input data
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return;
    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);

    // Prepare mode strings
    const char *modes[] = {"r", "w", "a"};
    size_t mode_index = Data[0] % (sizeof(modes) / sizeof(modes[0]));
    const char *mode = modes[mode_index];

    // gzdopen
    gzFile gz_file = gzdopen(fd, mode);
    if (gz_file == NULL) {
        close(fd);
        return;
    }

    // gzeof
    int eof = gzeof(gz_file);

    // gzgetc_
    int c = gzgetc_(gz_file);

    // gzdirect
    int direct = gzdirect(gz_file);

    // Conditionally use gzflush only if mode is not 'r'
    if (mode[0] != 'r') {
        int flush_result = gzflush(gz_file, Z_FINISH);
    }

    // gzclose_r
    int close_result = gzclose_r(gz_file);

    // Cleanup
    close(fd);
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    fuzz_gzdopen_gzeof_gzgetc_gzdirect_gzclose_r(Data, Size);
    return 0;
}