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
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

static int create_dummy_file(const char *filename, const uint8_t *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) return -1;
    size_t written = fwrite(data, 1, size, file);
    fclose(file);
    return written == size ? 0 : -1;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a dummy file
    const char *dummy_filename = "./dummy_file";
    if (create_dummy_file(dummy_filename, Data, Size) != 0) return 0;

    // Open the dummy file to get a file descriptor
    int fd = open(dummy_filename, O_RDONLY);
    if (fd < 0) return 0;

    // Determine mode based on input data
    const char *modes[] = {"r", "w", "a"};
    const char *mode = modes[Data[0] % 3];

    // Test gzdopen
    gzFile gz = gzdopen(fd, mode);
    if (gz == NULL) {
        close(fd);
        return 0;
    }

    // Test gzeof
    int eof = gzeof(gz);

    // Test gzrewind
    int rewind_result = gzrewind(gz);

    // Test gzdirect
    int direct = gzdirect(gz);

    // Test gzflush with different flush modes
    int flush_modes[] = {Z_NO_FLUSH, Z_SYNC_FLUSH, Z_FULL_FLUSH, Z_FINISH};
    int flush_mode = flush_modes[Data[1] % 4];
    int flush_result = gzflush(gz, flush_mode);

    // Test gzclose_r
    int close_result = gzclose_r(gz);

    // Close the file descriptor if gzclose_r didn't close it
    if (close_result != Z_OK) {
        close(fd);
    }

    // Remove the dummy file
    remove(dummy_filename);

    return 0;
}