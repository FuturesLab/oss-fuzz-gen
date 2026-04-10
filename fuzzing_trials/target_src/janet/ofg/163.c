#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function-under-test
Janet janet_cfun_stream_close(int32_t argc, Janet *argv);

int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a Janet array
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet array from the input data
    Janet *janetArray = (Janet *)janet_smalloc(size);
    for (size_t i = 0; i < size / sizeof(Janet); i++) {
        janetArray[i] = janet_wrap_integer((int32_t)data[i]);
    }

    // Call the function-under-test
    janet_cfun_stream_close((int32_t)(size / sizeof(Janet)), janetArray);

    // Clean up
    janet_sfree(janetArray);
    janet_deinit();

    return 0;
}