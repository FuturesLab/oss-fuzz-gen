#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming kstring_t is defined as follows:
typedef struct {
    size_t l, m;
    char *s;
} kstring_t;

// Function signature for the function-under-test
char * haddextension(struct kstring_t *, const char *, int, const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Initialize kstring_t
    kstring_t kstr;
    kstr.l = size;
    kstr.m = size + 1; // Allow space for null terminator
    kstr.s = (char *)malloc(kstr.m);
    if (kstr.s == NULL) {
        return 0; // Failed to allocate memory
    }
    memcpy(kstr.s, data, size);
    kstr.s[size] = '\0'; // Null-terminate the string

    // Initialize other parameters
    const char *ext1 = "txt"; // Example extension
    int flag = 1; // Example flag value
    const char *ext2 = "bak"; // Another example extension

    // Call the function-under-test
    char *result = haddextension(&kstr, ext1, flag, ext2);

    // Free allocated memory
    free(kstr.s);

    // Free the result if dynamically allocated
    if (result != kstr.s) {
        free(result);
    }

    return 0;
}