#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Cast the input data to a char pointer
    const char *input = (const char *)data;

    // Call the function-under-test with the input data
    // The second parameter is the length of the input data
    int result = sqlite3_keyword_check(input, (int)size);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}