// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen64 at gzlib.c:293:16 in zlib.h
// gzread at gzread.c:392:13 in zlib.h
// gztell64 at gzlib.c:446:19 in zlib.h
// gzseek64 at gzlib.c:367:19 in zlib.h
// gzoffset at gzlib.c:490:17 in zlib.h
// gzoffset64 at gzlib.c:469:19 in zlib.h
// gzseek64 at gzlib.c:367:19 in zlib.h
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
#include <string.h>

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    char mode[2] = { 'r', '\0' };
    if (Size > 2) {
        mode[0] = Data[0] % 2 ? 'w' : 'r';
    }

    prepare_dummy_file(Data + 1, Size - 1);

    gzFile file = gzopen64("./dummy_file", mode);
    if (file == NULL) {
        return 0;
    }

    unsigned char buffer[1024];
    int bytesRead = gzread(file, buffer, sizeof(buffer));

    z_off64_t pos = gztell64(file);
    gzseek64(file, pos, SEEK_SET);

    z_off_t offset = gzoffset(file);
    z_off64_t offset64 = gzoffset64(file);

    if (bytesRead != -1) {
        gzseek64(file, 0, SEEK_SET);
    }

    gzclose(file);
    return 0;
}