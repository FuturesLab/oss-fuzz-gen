#include <stdint.h>
#include <stddef.h> // Include this to fix the 'unknown type name' error for size_t

// Assuming the function is declared in a header file or elsewhere
void janet_ev_dec_refcount();

int LLVMFuzzerTestOneInput_1495(const uint8_t *data, size_t size) {
    // Call the function-under-test
    janet_ev_dec_refcount();

    return 0;
}