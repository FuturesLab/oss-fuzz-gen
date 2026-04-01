#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_259(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int index = *((int*)data);

    // Call the function-under-test
    const char *option = sqlite3_compileoption_get(index);

    // Option can be NULL if the index is out of range
    if (option != NULL) {
        // Do something with the option, e.g., print it or process it
        // For the purpose of fuzzing, we don't need to do anything specific
    }

    return 0;
}