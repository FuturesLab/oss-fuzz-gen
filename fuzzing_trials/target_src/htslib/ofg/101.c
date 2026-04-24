#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
char *stringify_argv(int argc, char **argv);

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Ensure there is enough data to proceed
    if (size < 2) return 0;

    // Determine the number of arguments
    int argc = data[0] % 5 + 1; // Limit argc to a small number for testing
    char **argv = (char **)malloc(argc * sizeof(char *));
    if (!argv) return 0;

    size_t offset = 1;
    for (int i = 0; i < argc; i++) {
        // Ensure there is enough space for at least one character and null terminator
        if (offset >= size - 1) {
            argv[i] = strdup("");
        } else {
            size_t arg_len = (data[offset] % (size - offset)) + 1;
            argv[i] = (char *)malloc(arg_len + 1);
            if (!argv[i]) {
                // Clean up previously allocated memory
                for (int j = 0; j < i; j++) {
                    free(argv[j]);
                }
                free(argv);
                return 0;
            }
            memcpy(argv[i], &data[offset], arg_len);
            argv[i][arg_len] = '\0';
            offset += arg_len;
        }
    }

    // Call the function-under-test
    char *result = stringify_argv(argc, argv);

    // Clean up
    if (result) free(result);
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);

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

    LLVMFuzzerTestOneInput_101(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
