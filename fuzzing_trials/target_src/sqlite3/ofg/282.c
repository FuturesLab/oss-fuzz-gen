#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_282(const uint8_t *data, size_t size) {
    int error_code;
    const char *message;
    void *arg = (void *)0x1; // Non-null arbitrary pointer

    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer error code from the data
    error_code = *(int *)data;

    // Ensure the message is null-terminated
    message = (const char *)(data + sizeof(int));

    // Call the function-under-test
    sqlite3_log(error_code, message, arg);

    return 0;
}