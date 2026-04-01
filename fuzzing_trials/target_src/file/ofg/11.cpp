#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize a magic_set structure
    struct magic_set *ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;
    }

    // Ensure the data is null-terminated to use it as a string
    char *file_name = (char *)malloc(size + 1);
    if (file_name == NULL) {
        magic_close(ms);
        return 0;
    }
    memcpy(file_name, data, size);
    file_name[size] = '\0';

    // Call the function-under-test
    const char *result = magic_file(ms, file_name);

    // Clean up
    free(file_name);
    magic_close(ms);

    return 0;
}