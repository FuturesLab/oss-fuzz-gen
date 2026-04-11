#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern int janet_indexed_view(Janet, const Janet **, int32_t *);

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0; // Ensure there's enough data for a Janet object
    }

    // Initialize a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Prepare the output parameters for janet_indexed_view
    const Janet *view = NULL;
    int32_t length = 0;

    // Call the function-under-test
    janet_indexed_view(janet_obj, &view, &length);

    return 0;
}