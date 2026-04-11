#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Cast the input data to a Janet type
    Janet x = *(const Janet *)data;

    // Use a fixed integer value for types
    int types = 1; // Example type value, adjust as needed for testing

    // Call the function-under-test using the macro
    int result = janet_checktypes(x, types);

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}