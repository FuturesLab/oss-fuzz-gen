#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to create a ucl_object_iter_t
    if (size < sizeof(ucl_object_iter_t)) {
        return 0;
    }

    // Initialize a ucl_object_iter_t from the input data
    ucl_object_iter_t *iter = (ucl_object_iter_t *)data;

    // Call the function under test
    bool result = ucl_object_iter_chk_excpn(iter);

    // The result is not used further, as we are primarily interested in testing for crashes or undefined behavior
    (void)result;

    return 0;
}