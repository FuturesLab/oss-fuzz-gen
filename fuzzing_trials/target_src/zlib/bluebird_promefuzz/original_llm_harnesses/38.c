// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gztell64 at gzlib.c:446:19 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzoffset at gzlib.c:490:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzoffset64 at gzlib.c:469:19 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gztell at gzlib.c:461:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
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
#include <string.h>
#include <zlib.h>

static gzFile initialize_gzfile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) return NULL;

    gzFile gzfile = gzdopen(fileno(file), "rb");
    if (!gzfile) fclose(file);

    return gzfile;
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    gzFile file = initialize_gzfile(Data, Size);
    if (!file) return 0;

    // Test gztell64
    z_off64_t tell64 = gztell64(file);
    if (tell64 == -1) {
        gzclose(file);
        return 0;
    }

    // Test gzseek
    z_off_t seek = gzseek(file, 0, SEEK_SET);
    if (seek == -1) {
        gzclose(file);
        return 0;
    }

    // Test gzgetc
    int c = gzgetc(file);
    if (c == -1) {
        gzclose(file);
        return 0;
    }

    // Test gzoffset
    z_off_t offset = gzoffset(file);
    if (offset == -1) {
        gzclose(file);
        return 0;
    }

    // Test gzoffset64
    z_off64_t offset64 = gzoffset64(file);
    if (offset64 == -1) {
        gzclose(file);
        return 0;
    }

    // Test gztell
    z_off_t tell = gztell(file);
    if (tell == -1) {
        gzclose(file);
        return 0;
    }

    gzclose(file);
    return 0;
}