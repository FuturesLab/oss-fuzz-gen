#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Function-under-test
Janet janet_cfun_stream_close(int32_t argc, Janet *argv);

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure that size is at least the size of an int32_t
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Use the first 4 bytes of data to determine argc
    int32_t argc = *(int32_t *)data;
    if (argc < 0) {
        argc = -argc; // Ensure argc is non-negative
    }

    // Allocate memory for Janet array
    Janet *argv = (Janet *)malloc(argc * sizeof(Janet));
    if (argv == NULL) {
        return 0;
    }

    // Initialize Janet elements in argv
    for (int32_t i = 0; i < argc; i++) {
        argv[i] = janet_wrap_integer((int32_t)(data[i % size]));
    }

    // Call the function-under-test
    janet_cfun_stream_close(argc, argv);

    // Free allocated memory
    free(argv);

    return 0;
}