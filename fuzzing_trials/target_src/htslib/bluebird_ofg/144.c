#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Declare the external function
extern int sam_open_mode(char *, const char *, const char *);

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to create three strings
    if (size < 6) {
        return 0;
    }

    // Allocate buffers for the strings
    char buffer1[3];
    char buffer2[3];
    char buffer3[3];

    // Copy data into the buffers ensuring null-termination
    memcpy(buffer1, data, 2);
    buffer1[2] = '\0';

    memcpy(buffer2, data + 2, 2);
    buffer2[2] = '\0';

    memcpy(buffer3, data + 4, 2);
    buffer3[2] = '\0';

    // Call the function under test
    sam_open_mode(buffer1, buffer2, buffer3);

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

    LLVMFuzzerTestOneInput_144(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
