#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    hFILE *file;
    void *buffer;
    ssize_t result;
    size_t buffer_size;

    // Ensure size is non-zero to avoid division by zero
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to use with hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the file using hdopen
    file = hdopen(fd, "r");
    if (file == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Allocate a buffer for reading
    buffer_size = size / 2 + 1; // Ensure buffer is non-zero
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        hclose(file);
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    result = hpeek(file, buffer, buffer_size);

    // Clean up
    free(buffer);
    hclose(file);
    close(fd);
    unlink(tmpl);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_12(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
