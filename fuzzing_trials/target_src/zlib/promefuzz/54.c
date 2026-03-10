// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzwrite at gzwrite.c:255:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzwrite at gzwrite.c:255:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzfread at gzread.c:435:18 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzfwrite at gzwrite.c:280:18 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static void fuzz_gzdopen_gzclose(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    // Ensure the mode string is null-terminated and valid
    char mode[4];
    if (Size < 3) {
        close(fd);
        return;
    }
    memcpy(mode, Data, 3);
    mode[3] = '\0';

    gzFile gz = gzdopen(fd, mode);
    if (gz != NULL) {
        gzclose(gz);
    }
    close(fd);
}

static void fuzz_gzwrite_gzclose(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    gzFile gz = gzdopen(fd, "w");
    if (gz != NULL) {
        gzwrite(gz, Data, Size);
        gzclose(gz);
    }
    close(fd);
}

static void fuzz_gzfread_gzclearerr(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    gzFile gz = gzdopen(fd, "w");
    if (gz != NULL) {
        gzwrite(gz, Data, Size);
        gzclose(gz);
    }
    close(fd);

    fd = open("./dummy_file", O_RDONLY);
    if (fd < 0) return;

    gz = gzdopen(fd, "r");
    if (gz != NULL) {
        char buffer[128];
        gzfread(buffer, 1, sizeof(buffer), gz);
        gzclearerr(gz);
        gzclose(gz);
    }
    close(fd);
}

static void fuzz_gzfwrite_gzclose(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    gzFile gz = gzdopen(fd, "w");
    if (gz != NULL) {
        gzfwrite(Data, 1, Size, gz);
        gzclose(gz);
    }
    close(fd);
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    fuzz_gzdopen_gzclose(Data, Size);
    fuzz_gzwrite_gzclose(Data, Size);
    fuzz_gzfread_gzclearerr(Data, Size);
    fuzz_gzfwrite_gzclose(Data, Size);
    return 0;
}