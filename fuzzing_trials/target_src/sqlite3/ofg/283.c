#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    int errorCode = 1; // Example error code, can be any integer
    const char *message = "Test log message"; // Example log message
    void *pArg = (void *)data; // Using data as the void* argument

    // Ensure size is non-zero to avoid passing NULL to the function
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    sqlite3_log(errorCode, message, pArg);

    return 0;
}

#ifdef __cplusplus
}
#endif