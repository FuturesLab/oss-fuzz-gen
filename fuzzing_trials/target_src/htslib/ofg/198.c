#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hfile.h"

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract a valid file descriptor and filename
    if (size < 4) {
        return 0;
    }

    // Extract an integer for the file descriptor from the data
    int fd = *((int *)data);

    // Extract a string for the filename from the remaining data
    const char *filename = (const char *)(data + 4);

    // Ensure the filename is null-terminated
    char *null_terminated_filename = (char *)malloc(size - 4 + 1);
    if (null_terminated_filename == NULL) {
        return 0;
    }
    memcpy(null_terminated_filename, filename, size - 4);
    null_terminated_filename[size - 4] = '\0';

    // Call the function-under-test
    hFILE *file = hdopen(fd, null_terminated_filename);

    // Clean up
    if (file != NULL) {
        hclose(file);
    }
    free(null_terminated_filename);

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

    LLVMFuzzerTestOneInput_198(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
