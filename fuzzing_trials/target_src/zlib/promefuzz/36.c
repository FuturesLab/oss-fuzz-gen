// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:288:16 in zlib.h
// gzsetparams at gzwrite.c:630:13 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzseek at gzlib.c:438:17 in zlib.h
// gzclearerr at gzlib.c:531:14 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzclose_w at gzwrite.c:667:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static gzFile initialize_gzfile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;

    if (fwrite(Data, 1, Size, file) != Size) {
        fclose(file);
        return NULL;
    }
    fclose(file);

    gzFile gz = gzopen("./dummy_file", "wb");
    return gz;
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    gzFile gz = initialize_gzfile(Data, Size);
    if (!gz) return 0;

    int level = Data[0] % 10; // Compression level (0-9)
    int strategy = Data[1] % 4; // Strategy (0-3)

    gzsetparams(gz, level, strategy);

    for (size_t i = 2; i < Size; ++i) {
        gzputc(gz, Data[i]);
    }

    gzseek(gz, 0, SEEK_SET);
    gzclearerr(gz);

    int close_mode = Data[2] % 2;
    if (close_mode == 0) {
        gzclose(gz);
    } else {
        gzclose_w(gz);
    }

    return 0;
}