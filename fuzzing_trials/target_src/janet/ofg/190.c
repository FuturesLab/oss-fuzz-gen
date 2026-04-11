#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int janet_checkint(Janet j);

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to interpret as a Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Cast the data to a Janet value
    Janet j = *(const Janet *)data;

    // Call the function-under-test
    int result = janet_checkint(j);

    // Return 0 to indicate successful execution
    return 0;
}