#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function signature to be fuzzed
char *stringify_argv(int argc, char **argv);

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte of data to process
    if (size == 0) {
        return 0;
    }

    // Calculate the number of arguments
    int argc = data[0] % 10 + 1; // Limit the number of arguments to 10 for simplicity

    // Allocate memory for the arguments array
    char **argv = (char **)malloc(argc * sizeof(char *));
    if (argv == NULL) {
        return 0;
    }

    // Split the input data into arguments
    size_t offset = 1;
    for (int i = 0; i < argc; i++) {
        size_t arg_len = (size - offset) / (argc - i);
        argv[i] = (char *)malloc((arg_len + 1) * sizeof(char));
        if (argv[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(argv[j]);
            }
            free(argv);
            return 0;
        }
        memcpy(argv[i], data + offset, arg_len);
        argv[i][arg_len] = '\0';
        offset += arg_len;
    }

    // Call the function-under-test
    char *result = stringify_argv(argc, argv);

    // Free the result if it was dynamically allocated
    if (result != NULL) {
        free(result);
    }

    // Free the allocated memory for arguments
    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);

    return 0;
}