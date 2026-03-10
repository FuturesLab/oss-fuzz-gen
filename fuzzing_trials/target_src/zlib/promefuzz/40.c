// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzclose at gzclose.c:11:13 in zlib.h
// zlibVersion at zutil.c:27:22 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzputc at gzwrite.c:307:13 in zlib.h
// gzgets at gzread.c:562:16 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void fuzz_zlibVersion() {
    const char *version = zlibVersion();
    if (version) {
        printf("zlib version: %s\n", version);
    }
}

static void fuzz_gzerror(gzFile file) {
    int errnum;
    const char *error_message = gzerror(file, &errnum);
    if (error_message) {
        printf("gzerror: %s, errnum: %d\n", error_message, errnum);
    }
}

static void fuzz_gzputc(gzFile file, int c) {
    int result = gzputc(file, c);
    if (result == -1) {
        printf("gzputc error\n");
    } else {
        printf("gzputc wrote: %c\n", result);
    }
}

static void fuzz_gzgets(gzFile file, char *buf, int len) {
    char *result = gzgets(file, buf, len);
    if (result) {
        printf("gzgets read: %s\n", result);
    } else {
        printf("gzgets error or EOF\n");
    }
}

static void fuzz_gzputs(gzFile file, const char *s) {
    int result = gzputs(file, s);
    if (result == -1) {
        printf("gzputs error\n");
    } else {
        printf("gzputs wrote: %d bytes\n", result);
    }
}

static void fuzz_gzgetc(gzFile file) {
    int result = gzgetc(file);
    if (result == -1) {
        printf("gzgetc error or EOF\n");
    } else {
        printf("gzgetc read: %c\n", result);
    }
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    fuzz_zlibVersion();

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    gzFile gzfile = gzopen("./dummy_file", "rb");
    if (!gzfile) return 0;

    // Fuzz gzerror
    fuzz_gzerror(gzfile);

    // Fuzz gzgetc
    fuzz_gzgetc(gzfile);

    // Prepare buffer for gzgets
    char buffer[256];
    fuzz_gzgets(gzfile, buffer, sizeof(buffer));

    gzclose(gzfile);

    gzfile = gzopen("./dummy_file", "wb");
    if (!gzfile) return 0;

    // Fuzz gzputc
    fuzz_gzputc(gzfile, Data[0]);

    // Prepare a null-terminated string for gzputs
    char *str = (char *)malloc(Size + 1);
    if (str) {
        memcpy(str, Data, Size);
        str[Size] = '\0';
        fuzz_gzputs(gzfile, str);
        free(str);
    }

    gzclose(gzfile);

    return 0;
}