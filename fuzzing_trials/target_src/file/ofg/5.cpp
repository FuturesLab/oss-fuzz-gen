#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

// Ensure C linkage for the function-under-test
extern "C" {
    #include <magic.h>
}

// Fuzzing harness for magic_compile function
extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the data is null-terminated for use as a string
    char *file_data = (char *)malloc(size + 1);
    if (file_data == NULL) {
        magic_close(ms);
        return 0; // If memory allocation fails, exit early
    }
    memcpy(file_data, data, size);
    file_data[size] = '\0';

    // Call the function-under-test
    magic_compile(ms, file_data);

    // Clean up resources
    free(file_data);
    magic_close(ms);

    return 0;
}