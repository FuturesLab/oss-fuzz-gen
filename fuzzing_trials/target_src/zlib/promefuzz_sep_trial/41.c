// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzsetparams at gzwrite.c:630:13 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzclose_w at gzwrite.c:667:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static gzFile create_dummy_gzfile() {
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) return NULL;
    fclose(file);
    return gzopen("./dummy_file", "wb+");
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    gzFile file = create_dummy_gzfile();
    if (!file) return 0;

    // Fuzz gzputc
    gzputc(file, Data[0]);

    // Fuzz gzsetparams with random level and strategy
    if (Size >= 2) {
        int level = Data[1] % 10; // Compression level [0-9]
        int strategy = Data[1] % 5; // Strategy [0-4]
        gzsetparams(file, level, strategy);
    }

    // Fuzz gzseek
    if (Size >= 3) {
        z_off_t offset = Data[2] % 100; // Arbitrary offset
        gzseek(file, offset, SEEK_SET);
    }

    // Fuzz gzclearerr
    gzclearerr(file);

    // Fuzz gzclose_w
    gzclose_w(file);

    // Reopen file for reading
    file = gzopen("./dummy_file", "rb");
    if (!file) return 0;

    // Fuzz gzclose
    gzclose(file);

    return 0;
}