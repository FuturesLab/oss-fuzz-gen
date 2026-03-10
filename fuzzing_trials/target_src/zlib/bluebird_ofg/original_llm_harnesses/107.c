#include <stdint.h>
#include <stddef.h>
#include <zlib.h> // Include the zlib header for the zError function

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Initialize an integer variable to pass to zError
    int errorCode = 0;

    // Ensure that size is not zero to avoid accessing data[0] when data is empty
    if (size > 0) {
        // Use the first byte of data to set the errorCode
        errorCode = (int)data[0];
    }

    // Call the zError function with the errorCode
    const char *errorString = zError(errorCode);

    // To avoid unused variable warning, you can print the errorString
    // or handle it in some way. Here, we'll just ensure it's not null.
    if (errorString != NULL) {
        // Do something with errorString if needed
    }

    return 0;
}