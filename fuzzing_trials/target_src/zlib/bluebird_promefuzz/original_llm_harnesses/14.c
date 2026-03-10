// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdirect at gzread.c:623:13 in zlib.h
// gzrewind at gzlib.c:346:13 in zlib.h
// gzflush at gzwrite.c:603:13 in zlib.h
// gzeof at gzlib.c:498:13 in zlib.h
// gzdopen at gzlib.c:298:16 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

static void fuzz_gzdirect(gzFile file) {
    int result = gzdirect(file);
    (void)result;
}

static void fuzz_gzrewind(gzFile file) {
    int result = gzrewind(file);
    (void)result;
}

static void fuzz_gzflush(gzFile file) {
    int result = gzflush(file, Z_SYNC_FLUSH);
    (void)result;
}

static void fuzz_gzeof(gzFile file) {
    int result = gzeof(file);
    (void)result;
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file for reading
    int fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) return 0;

    // Try different modes for gzdopen
    const char *modes[] = {"r", "rb", "r+", "wb", "ab"};
    size_t num_modes = sizeof(modes) / sizeof(modes[0]);

    for (size_t i = 0; i < num_modes; i++) {
        gzFile gz_file = gzdopen(fd, modes[i]);
        if (!gz_file) continue;

        // Fuzz various functions
        fuzz_gzdirect(gz_file);
        fuzz_gzrewind(gz_file);
        fuzz_gzflush(gz_file);
        fuzz_gzeof(gz_file);

        // Close the gzFile to free resources
        gzclose(gz_file);

        // Reopen the file descriptor for the next iteration
        fd = open("./dummy_file", O_RDONLY);
        if (fd == -1) break;
    }

    // Close the file descriptor if still open
    if (fd != -1) close(fd);

    return 0;
}