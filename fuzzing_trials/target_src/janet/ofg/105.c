#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming the JanetTable structure is defined somewhere in the included headers
typedef struct {
    // Placeholder for the actual structure members
    int dummy;
} JanetTable;

// Function signature for the function-under-test
void janet_env_lookup_into(JanetTable *env, JanetTable *dest, const char *key, int flags);

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Initialize JanetTable structures
    JanetTable env;
    JanetTable dest;

    // Ensure the data size is sufficient to extract a string and an integer
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract a string from the data
    size_t key_len = size - sizeof(int);
    char *key = (char *)malloc(key_len + 1);
    if (key == NULL) {
        return 0;
    }
    memcpy(key, data, key_len);
    key[key_len] = '\0'; // Null-terminate the string

    // Extract an integer from the data
    int flags;
    memcpy(&flags, data + key_len, sizeof(int));

    // Call the function-under-test
    janet_env_lookup_into(&env, &dest, key, flags);

    // Free allocated memory
    free(key);

    return 0;
}