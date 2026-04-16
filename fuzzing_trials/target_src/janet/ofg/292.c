#include <stdint.h>
#include <stddef.h>

// Assuming the function is defined in an external library
extern void janet_ev_inc_refcount();

int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    // Call the function-under-test
    janet_ev_inc_refcount();

    return 0;
}