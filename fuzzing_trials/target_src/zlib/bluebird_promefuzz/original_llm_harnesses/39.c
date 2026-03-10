// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzfwrite at gzwrite.c:280:18 in zlib.h
// gzread at gzread.c:392:13 in zlib.h
// gzfread at gzread.c:435:18 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

static void fuzz_gzdopen(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;

    // Ensure the mode string is null-terminated and reasonable
    char mode[4] = "r";
    if (Size > 0) {
        mode[0] = Data[0] % 3 == 0 ? 'r' : (Data[0] % 3 == 1 ? 'w' : 'a');
    }
    gzFile file = gzdopen(fd, mode);
    if (file) {
        gzclose(file);
    } else {
        close(fd);
    }
}

static void fuzz_gzclearerr(gzFile file) {
    gzclearerr(file);
}

static void fuzz_gzclose(gzFile file) {
    gzclose(file);
}

static void fuzz_gzfwrite(gzFile file, const uint8_t *Data, size_t Size) {
    size_t items_written = gzfwrite(Data, 1, Size, file);
    (void)items_written; // Suppress unused variable warning
}

static void fuzz_gzread(gzFile file, size_t Size) {
    uint8_t *buffer = (uint8_t *)malloc(Size);
    if (buffer) {
        gzread(file, buffer, Size);
        free(buffer);
    }
}

static void fuzz_gzfread(gzFile file, size_t Size) {
    uint8_t *buffer = (uint8_t *)malloc(Size);
    if (buffer) {
        gzfread(buffer, 1, Size, file);
        free(buffer);
    }
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return 0;

    // Write the data to the dummy file
    write(fd, Data, Size);
    lseek(fd, 0, SEEK_SET);

    // Fuzz gzdopen
    fuzz_gzdopen(Data, Size);

    // Rewind and open the file for reading
    lseek(fd, 0, SEEK_SET);
    gzFile file = gzdopen(fd, "r");
    if (file) {
        // Fuzz gzclearerr
        fuzz_gzclearerr(file);

        // Fuzz gzread
        fuzz_gzread(file, Size);

        // Fuzz gzfread
        fuzz_gzfread(file, Size);

        // Fuzz gzclose
        fuzz_gzclose(file);
    } else {
        close(fd);
    }

    // Rewind and open the file for writing
    lseek(fd, 0, SEEK_SET);
    file = gzdopen(fd, "w");
    if (file) {
        // Fuzz gzfwrite
        fuzz_gzfwrite(file, Data, Size);

        // Fuzz gzclose
        fuzz_gzclose(file);
    } else {
        close(fd);
    }

    return 0;
}