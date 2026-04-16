#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming JanetTable is defined somewhere in the included headers
typedef struct {
    // Placeholder for actual JanetTable structure members
    int dummy;
} JanetTable;

// Function prototype for the function-under-test
void janet_env_lookup_into(JanetTable *env, JanetTable *dest, const char *key, int flags);

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for JanetTable structures
    JanetTable env;
    JanetTable dest;

    // Copy data to a new buffer and ensure it is null-terminated
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Use a fixed integer value for flags
    int flags = 0;

    // Call the function-under-test
    janet_env_lookup_into(&env, &dest, key, flags);

    // Free allocated memory
    free(key);

    return 0;
}