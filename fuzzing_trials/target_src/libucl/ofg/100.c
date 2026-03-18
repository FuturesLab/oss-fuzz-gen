#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid ucl_object_iter_t
    if (size < sizeof(ucl_object_iter_t)) {
        return 0;
    }

    // Create a ucl_object_iter_t from the input data
    ucl_object_iter_t *iter = (ucl_object_iter_t *)data;

    // Call the function-under-test
    bool result = ucl_object_iter_chk_excpn(iter);

    // Use the result to prevent compiler optimizations
    if (result) {
        // Do something trivial
        volatile int dummy = 0;
        dummy++;
    }

    return 0;
}