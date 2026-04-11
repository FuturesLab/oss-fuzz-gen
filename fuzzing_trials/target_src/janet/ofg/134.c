#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h>

extern int64_t janet_optinteger64(const Janet *argv, int32_t n, int32_t argc, int64_t def);

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + sizeof(int64_t)) {
        return 0; // Not enough data to fill all parameters
    }

    // Initialize parameters
    Janet argv[1];
    memcpy(argv, data, sizeof(Janet));
    
    int32_t n = (int32_t)data[sizeof(Janet)];
    int32_t argc = (int32_t)data[sizeof(Janet) + sizeof(int32_t)];
    int64_t def = *(int64_t *)(data + sizeof(Janet) + sizeof(int32_t) * 2);

    // Call the function-under-test
    int64_t result = janet_optinteger64(argv, n, argc, def);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}