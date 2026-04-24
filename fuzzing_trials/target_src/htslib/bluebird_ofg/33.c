#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for two null-terminated strings
    if (size < 4) return 0;

    // Allocate memory for the filename and mode strings
    char filename[256];
    char mode[4];

    // Copy data to filename and mode, ensuring null-termination
    size_t filename_len = (size < 255) ? size : 255;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    size_t mode_len = (size - filename_len < 3) ? size - filename_len : 3;
    memcpy(mode, data + filename_len, mode_len);
    mode[mode_len] = '\0';

    // Ensure filename is not empty
    if (filename[0] == '\0') return 0;

    // Create a temporary file to use as the filename
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the data to the temporary file
    write(fd, data, size);
    close(fd);

    // Call the function-under-test
    htsFile *file = hts_open(tmpl, mode);

    // Clean up
    if (file != NULL) {
        hts_close(file);
    }
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_33(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
