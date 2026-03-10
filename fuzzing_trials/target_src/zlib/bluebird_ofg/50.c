#include <stdint.h>
#include <stddef.h>
#include "zlib.h"  // Include the zlib header for the zError function

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure we have at least 4 bytes to form an int
    if (size < 4) {
        return 0;
    }

    // Convert the first 4 bytes of data to an int
    int errorCode = *(const int *)data;

    // Call the function-under-test
    const char *errorString = zError(errorCode);

    // Use the errorString to avoid unused variable warning
    if (errorString) {
        // Do something trivial with errorString, such as checking its length
        size_t length = 0;
        while (errorString[length] != '\0') {
            length++;
        }
    }

    return 0;
}