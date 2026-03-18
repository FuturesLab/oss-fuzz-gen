#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include this for malloc and free
#include <string.h>  // Include this for memcpy
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the test
    if (size < 4) {
        return 0;
    }

    // Extract an integer from the data
    int errCode = *(const int*)data;

    // Ensure there is a null-terminated string in the data
    const char *message = (const char *)(data + 4);
    size_t messageLength = size - 4;

    // Allocate memory for the null-terminated string
    char *logMessage = (char *)malloc(messageLength + 1);
    if (!logMessage) {
        return 0;
    }

    // Copy the message and ensure it's null-terminated
    memcpy(logMessage, message, messageLength);
    logMessage[messageLength] = '\0';

    // Call the function under test
    sqlite3_log(errCode, logMessage, NULL);

    // Free allocated memory
    free(logMessage);

    return 0;
}