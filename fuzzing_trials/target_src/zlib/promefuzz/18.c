// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzbuffer at gzlib.c:322:13 in zlib.h
// gzrewind at gzlib.c:346:13 in zlib.h
// gzdirect at gzread.c:623:13 in zlib.h
// gzflush at gzwrite.c:603:13 in zlib.h
// gzclose_r at gzread.c:641:13 in zlib.h
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

static int create_dummy_file(const char *filename, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return -1;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);
    return 0;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    const char *filename = "./dummy_file";
    if (create_dummy_file(filename, Data, Size) != 0) {
        return 0;
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    // Use a simple mode string for gzdopen
    const char *mode = "rb";
    gzFile gzfile = gzdopen(fd, mode);
    if (gzfile == NULL) {
        close(fd);
        return 0;
    }

    // Attempt to set buffer size
    gzbuffer(gzfile, 8192);

    // Test gzrewind function
    gzrewind(gzfile);

    // Test gzdirect function
    gzdirect(gzfile);

    // Test gzflush function (using Z_SYNC_FLUSH)
    gzflush(gzfile, Z_SYNC_FLUSH);

    // Close the gzFile
    gzclose_r(gzfile);

    return 0;
}