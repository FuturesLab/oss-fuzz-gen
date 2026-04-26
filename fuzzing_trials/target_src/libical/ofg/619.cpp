extern "C" {
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h> // Include for uint8_t

    void icalmemory_append_char(char **str, char **pos, size_t *buf_size, char ch);
}

extern "C" int LLVMFuzzerTestOneInput_619(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to proceed
    }

    // Initialize the buffer and its size
    size_t buf_size = size + 1; // Ensure there's space for the null terminator
    char *buffer = (char *)malloc(buf_size);
    if (buffer == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy data into buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Set the position pointer to the start of the buffer
    char *pos = buffer;

    // Call the function-under-test
    icalmemory_append_char(&buffer, &pos, &buf_size, (char)data[0]);

    // Free allocated memory
    free(buffer);

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

    LLVMFuzzerTestOneInput_619(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
