#include <stddef.h>
#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include the library for malloc and free

int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely pass as a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Return if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    int result = sqlite3_compileoption_used(null_terminated_data);

    // Clean up
    free(null_terminated_data);

    return 0;
}