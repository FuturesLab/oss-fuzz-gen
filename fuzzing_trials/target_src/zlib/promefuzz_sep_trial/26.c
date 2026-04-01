// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzeof at gzlib.c:498:13 in zlib.h
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
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <zlib.h>

static int create_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return -1;
    fwrite(Data, 1, Size, file);
    fclose(file);
    return open("./dummy_file", O_RDONLY);
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the input data
    int fd = create_dummy_file(Data, Size);
    if (fd < 0) return 0;

    // Prepare mode string
    char mode[4] = {0};
    mode[0] = Data[0] % 3 == 0 ? 'r' : (Data[0] % 3 == 1 ? 'w' : 'a');
    mode[1] = '\0';

    // Test gzdopen
    gzFile gz_file = gzdopen(fd, mode);
    if (!gz_file) {
        close(fd);
        return 0;
    }

    // Test gzeof
    int eof = gzeof(gz_file);

    // Test gzrewind
    int rewind_result = gzrewind(gz_file);

    // Test gzdirect
    int direct = gzdirect(gz_file);

    // Test gzflush if mode is 'w'
    if (mode[0] == 'w') {
        int flush_result = gzflush(gz_file, Z_FINISH);
    }

    // Test gzclose_r
    int close_result = gzclose_r(gz_file);

    return 0;
}