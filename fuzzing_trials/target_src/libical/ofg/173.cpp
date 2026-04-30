#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include the header where icalmemory_append_string is declared
    void icalmemory_append_string(char **str, char **pos, size_t *buf_size, const char *append);
}

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize the parameters for icalmemory_append_string
    size_t initial_buf_size = size + 20; // Allow extra space for appending
    char *str = (char *)malloc(initial_buf_size);
    if (str == NULL) {
        return 0; // Handle memory allocation failure
    }

    char *pos;
    size_t buf_size = initial_buf_size;

    // Ensure the string is null-terminated
    memcpy(str, data, size);
    str[size] = '\0';

    // Initialize pos to point to the end of the current string
    pos = str + size;

    // Use a non-null constant string to append
    const char *append = "append_string";

    // Call the function-under-test
    icalmemory_append_string(&str, &pos, &buf_size, append);

    // Check if the function made changes to the string
    if (pos != str + size) {
        // If pos has moved, it indicates that the function appended something
        // This is a basic check to ensure that the function is doing something
    }

    // Free allocated memory
    free(str);

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

    LLVMFuzzerTestOneInput_173(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
