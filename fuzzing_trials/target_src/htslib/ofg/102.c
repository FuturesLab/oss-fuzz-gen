#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// The function-under-test
char *stringify_argv(int argc, char **argv);

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 2) return 0;

    // Determine the number of arguments
    int argc = data[0] % 10 + 1; // Limit argc to a reasonable number (1-10)
    char **argv = (char **)malloc(argc * sizeof(char *));
    
    if (argv == NULL) return 0;

    size_t offset = 1;
    for (int i = 0; i < argc; ++i) {
        if (offset >= size) {
            argv[i] = strdup("");
        } else {
            // Calculate the length of this argument
            size_t arg_len = (size - offset) / (argc - i);
            argv[i] = (char *)malloc(arg_len + 1);
            if (argv[i] == NULL) {
                for (int j = 0; j < i; ++j) {
                    free(argv[j]);
                }
                free(argv);
                return 0;
            }
            memcpy(argv[i], data + offset, arg_len);
            argv[i][arg_len] = '\0';
            offset += arg_len;
        }
    }

    // Call the function-under-test
    char *result = stringify_argv(argc, argv);

    // Clean up
    free(result);
    for (int i = 0; i < argc; ++i) {
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

    LLVMFuzzerTestOneInput_102(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
