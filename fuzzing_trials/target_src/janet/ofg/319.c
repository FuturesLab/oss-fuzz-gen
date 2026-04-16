#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a Janet string from the input data
    JanetString janetStr = janet_string(data, size);

    // Wrap the JanetString in a Janet value
    Janet janetValue = janet_wrap_string(janetStr);

    // Call the function-under-test
    JanetString result = janet_unwrap_string(janetValue);

    // Clean up Janet
    janet_deinit();

    return 0;
}