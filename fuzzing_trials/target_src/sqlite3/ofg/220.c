#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_220(const uint8_t *data, size_t size) {
    int errorCode;

    // Ensure that the size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Copy the first 4 bytes of data into errorCode
    errorCode = *(const int *)data;

    // Call the function-under-test
    const char *errorStr = sqlite3_errstr(errorCode);

    // Use the result to avoid any compiler optimizations that might remove the call
    if (errorStr) {
        // Do something trivial with errorStr, like checking its length
        volatile size_t len = 0;
        while (errorStr[len] != '\0') {
            len++;
        }
    }

    return 0;
}