#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Cast the data to a Janet type
    Janet janet_obj = *(const Janet *)data;

    // Call the function-under-test
    int result = janet_gcunroot(janet_obj);

    return 0;
}