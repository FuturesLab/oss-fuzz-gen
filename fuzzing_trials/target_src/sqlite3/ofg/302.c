#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    // Ensure that the size is not zero to avoid passing a NULL pointer
    if (size == 0) {
        return 0;
    }

    // Cast the data to a const char pointer
    const char *input = (const char *)data;

    // Call the function-under-test
    // The second parameter is the length of the string, which is the size of the input data
    int result = sqlite3_keyword_check(input, (int)size);

    // Use the result in some way, here we just return it for completeness
    (void)result; // Suppress unused variable warning

    return 0;
}