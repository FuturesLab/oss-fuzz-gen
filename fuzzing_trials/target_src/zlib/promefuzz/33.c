// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// zlibVersion at zutil.c:27:22 in zlib.h
// gzerror at gzlib.c:513:22 in zlib.h
// gzgets at gzread.c:562:16 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzopen at gzlib.c:288:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void test_zlibVersion() {
    const char *version = zlibVersion();
    if (version) {
        printf("zlib version: %s\n", version);
    }
}

static void test_gzerror(gzFile file) {
    int errnum;
    const char *error = gzerror(file, &errnum);
    if (error) {
        printf("gzerror: %s, errnum: %d\n", error, errnum);
    }
}

static void test_gzgets(gzFile file) {
    char buffer[256];
    if (gzgets(file, buffer, sizeof(buffer)) != NULL) {
        printf("gzgets: %s\n", buffer);
    }
}

static void test_gzputs(gzFile file, const uint8_t *Data, size_t Size) {
    char *buffer = (char *)malloc(Size + 1);
    if (buffer) {
        memcpy(buffer, Data, Size);
        buffer[Size] = '\0';
        int bytes_written = gzputs(file, buffer);
        if (bytes_written == -1) {
            test_gzerror(file);
        } else {
            printf("gzputs: wrote %d bytes\n", bytes_written);
        }
        free(buffer);
    }
}

static void test_gzgetc(gzFile file) {
    int c = gzgetc(file);
    if (c != -1) {
        printf("gzgetc: %c\n", c);
    } else {
        test_gzerror(file);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    test_zlibVersion();

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    gzFile gzfile = gzopen("./dummy_file", "rb");
    if (gzfile) {
        test_gzgets(gzfile);
        test_gzgetc(gzfile);
        gzclose(gzfile);
    }

    gzfile = gzopen("./dummy_file", "wb");
    if (gzfile) {
        test_gzputs(gzfile, Data, Size);
        gzclose(gzfile);
    }

    return 0;
}