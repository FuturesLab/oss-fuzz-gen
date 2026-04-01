// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzdopen at gzlib.c:298:16 in zlib.h
// gzread at gzread.c:392:13 in zlib.h
// gzgetc at gzread.c:469:13 in zlib.h
// gzputs at gzwrite.c:350:13 in zlib.h
// gzprintf at gzwrite.c:487:15 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

static int create_dummy_file(const char *filename, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(filename, "wb");
    if (!file) return -1;
    size_t written = fwrite(Data, 1, Size, file);
    fclose(file);
    return written == Size ? 0 : -1;
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Need at least one byte for mode

    // Create a dummy file to work with
    const char *dummy_filename = "./dummy_file";
    if (create_dummy_file(dummy_filename, Data, Size) != 0) return 0;

    // Open the dummy file to get a file descriptor
    int fd = open(dummy_filename, O_RDWR);
    if (fd < 0) return 0;

    // Prepare mode string
    char mode[2] = {Data[0] % 3 == 0 ? 'r' : (Data[0] % 3 == 1 ? 'w' : 'a'), '\0'};

    // Test gzdopen
    gzFile gzfile = gzdopen(fd, mode);
    if (gzfile == NULL) {
        close(fd);
        return 0;
    }

    // Buffer for reading and writing
    unsigned char buf[1024];
    size_t buf_len = sizeof(buf) < Size ? sizeof(buf) : Size;

    // Test gzread if mode is 'r'
    if (mode[0] == 'r') {
        gzread(gzfile, buf, buf_len);
    }

    // Test gzgetc if mode is 'r'
    if (mode[0] == 'r') {
        gzgetc(gzfile);
    }

    // Test gzputs if mode is 'w'
    if (mode[0] == 'w') {
        char *null_terminated_data = (char *)malloc(Size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';
            gzputs(gzfile, null_terminated_data);
            free(null_terminated_data);
        }
    }

    // Test gzprintf if mode is 'w'
    if (mode[0] == 'w') {
        gzprintf(gzfile, "Fuzzing data: %.*s\n", (int)Size, Data);
    }

    // Cleanup
    gzclose(gzfile);
    close(fd);

    return 0;
}