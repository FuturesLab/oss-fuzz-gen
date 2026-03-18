// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gztell at gzlib.c:461:17 in zlib.h
// gztell64 at gzlib.c:446:19 in zlib.h
// gzseek64 at gzlib.c:367:19 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
// gzoffset at gzlib.c:490:17 in zlib.h
// gzoffset64 at gzlib.c:469:19 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static void fuzz_gztell(gzFile file) {
    z_off_t offset = gztell(file);
    if (offset == -1) {
        perror("gztell error");
    }
}

static void fuzz_gztell64(gzFile file) {
    z_off64_t offset = gztell64(file);
    if (offset == -1) {
        perror("gztell64 error");
    }
}

static void fuzz_gzseek64(gzFile file) {
    z_off64_t offset = 0;
    int whence = SEEK_SET;
    z_off64_t result = gzseek64(file, offset, whence);
    if (result == -1) {
        perror("gzseek64 error");
    }
}

static void fuzz_gzseek(gzFile file) {
    z_off_t offset = 0;
    int whence = SEEK_SET;
    z_off_t result = gzseek(file, offset, whence);
    if (result == -1) {
        perror("gzseek error");
    }
}

static void fuzz_gzoffset(gzFile file) {
    z_off_t offset = gzoffset(file);
    if (offset == -1) {
        perror("gzoffset error");
    }
}

static void fuzz_gzoffset64(gzFile file) {
    z_off64_t offset = gzoffset64(file);
    if (offset == -1) {
        perror("gzoffset64 error");
    }
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Write data to a dummy file for gzFile operations
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        perror("Failed to open dummy file");
        return 0;
    }

    if (fwrite(Data, 1, Size, dummy_file) != Size) {
        perror("Failed to write to dummy file");
        fclose(dummy_file);
        return 0;
    }
    fclose(dummy_file);

    // Open the dummy file as a gzFile
    gzFile file = gzopen("./dummy_file", "rb");
    if (!file) {
        perror("Failed to open gzFile");
        return 0;
    }

    // Fuzz the target functions
    fuzz_gztell(file);
    fuzz_gztell64(file);
    fuzz_gzseek64(file);
    fuzz_gzseek(file);
    fuzz_gzoffset(file);
    fuzz_gzoffset64(file);

    // Clean up
    if (gzclose(file) != Z_OK) {
        perror("Failed to close gzFile");
    }

    return 0;
}