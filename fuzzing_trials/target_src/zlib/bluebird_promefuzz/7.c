#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include "fcntl.h"
#include "zlib.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    int fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    const char *modes[] = {"r", "rb", "w", "wb", "a", "ab"};
    const char *mode = modes[Data[0] % (sizeof(modes) / sizeof(modes[0]))];
    
    gzFile gz_file = gzdopen(fd, mode);
    if (!gz_file) {
        close(fd);
        return 0;
    }

    // Test gzdirect
    int direct = gzdirect(gz_file);

    // Test gzrewind
    int rewind_result = gzrewind(gz_file);

    // Test gzflush
    int flush_result = gzflush(gz_file, Z_FINISH);

    // Test gzeof
    int eof = gzeof(gz_file);

    // Cleanup
    int close_result = gzclose_r(gz_file);

    return 0;
}