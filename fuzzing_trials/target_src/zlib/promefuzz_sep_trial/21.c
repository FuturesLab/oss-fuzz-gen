// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzeof at gzlib.c:498:13 in zlib.h
// gzrewind at gzlib.c:346:13 in zlib.h
// gzdirect at gzread.c:623:13 in zlib.h
// gzflush at gzwrite.c:603:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Open the dummy file
    int fd = open("./dummy_file", O_RDONLY);
    if (fd == -1) return 0;

    // Prepare mode strings
    const char *modes[] = {"r", "w", "a", "rb", "wb", "ab"};
    size_t num_modes = sizeof(modes) / sizeof(modes[0]);

    // Fuzz gzdopen with different modes
    for (size_t i = 0; i < num_modes; ++i) {
        gzFile gz = gzdopen(dup(fd), modes[i]); // Use dup to get a new file descriptor for each gzdopen
        if (gz != NULL) {
            // Test gzeof
            gzeof(gz);

            // Test gzrewind
            gzrewind(gz);

            // Test gzdirect
            gzdirect(gz);

            // Test gzflush with Z_SYNC_FLUSH
            gzflush(gz, Z_SYNC_FLUSH);

            // Close the gzFile
            gzclose(gz); // Use gzclose instead of gzclose_r to ensure proper cleanup
        }
    }

    // Close the original file descriptor
    close(fd);

    return 0;
}