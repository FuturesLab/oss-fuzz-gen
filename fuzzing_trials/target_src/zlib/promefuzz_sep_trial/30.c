// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzwrite at gzwrite.c:255:13 in zlib.h
// gzsetparams at gzwrite.c:630:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzfread at gzread.c:435:18 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

static gzFile initialize_gzfile_for_write() {
    return gzopen("./dummy_file", "wb");
}

static gzFile initialize_gzfile_for_read() {
    return gzopen("./dummy_file", "rb");
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0; // Ensure there's enough data to access Data[0] and Data[1]
    }

    // Prepare a buffer for reading and writing
    char buffer[1024];
    size_t buffer_size = sizeof(buffer) < Size ? sizeof(buffer) : Size;

    // Initialize gzFile for writing
    gzFile gzfile_write = initialize_gzfile_for_write();
    if (gzfile_write == NULL) {
        return 0; // Early exit if file cannot be opened for writing
    }

    // Fuzz gzwrite
    gzwrite(gzfile_write, Data, buffer_size);

    // Fuzz gzsetparams with random level and strategy
    gzsetparams(gzfile_write, Data[0] % 10, Data[1] % 4);

    // Close the write file
    gzclose(gzfile_write);

    // Initialize gzFile for reading
    gzFile gzfile_read = initialize_gzfile_for_read();
    if (gzfile_read == NULL) {
        return 0; // Early exit if file cannot be opened for reading
    }

    // Fuzz gzfread
    gzfread(buffer, 1, buffer_size, gzfile_read);

    // Fuzz gzclearerr
    gzclearerr(gzfile_read);

    // Close the read file
    gzclose(gzfile_read);

    return 0;
}