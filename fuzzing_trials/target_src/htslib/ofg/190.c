#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
char *stringify_argv(int argc, char **argv);

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Determine the number of arguments
    int argc = data[0] % 10 + 1; // Limit the number of arguments to a reasonable number (1-10)

    // Allocate memory for the argument pointers
    char **argv = (char **)malloc(argc * sizeof(char *));
    if (argv == NULL) {
        return 0;
    }

    // Allocate memory for each argument string
    size_t offset = 1;
    for (int i = 0; i < argc; i++) {
        if (offset >= size) {
            argv[i] = strdup("default"); // Use a default string if we run out of data
        } else {
            size_t arg_len = (data[offset] % 10) + 1; // Limit each argument length to 1-10
            if (offset + arg_len >= size) {
                arg_len = size - offset - 1; // Adjust length to avoid overflow
            }
            argv[i] = (char *)malloc((arg_len + 1) * sizeof(char));
            if (argv[i] == NULL) {
                argv[i] = strdup("default");
            } else {
                memcpy(argv[i], &data[offset], arg_len);
                argv[i][arg_len] = '\0';
                offset += arg_len;
            }
        }
    }

    // Call the function-under-test
    char *result = stringify_argv(argc, argv);

    // Clean up
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
    free(result);

    return 0;
}