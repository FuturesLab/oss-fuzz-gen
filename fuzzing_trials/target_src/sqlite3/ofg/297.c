#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    // Ensure the data size is non-zero to avoid passing a NULL pointer to the function
    if (size == 0) {
        return 0;
    }

    // Cast the data to a char pointer
    const char *input = (const char *)data;

    // Call the function-under-test
    int result = sqlite3_keyword_check(input, (int)size);

    // Use the result to prevent compiler optimizations that remove the function call
    (void)result;

    return 0;
}