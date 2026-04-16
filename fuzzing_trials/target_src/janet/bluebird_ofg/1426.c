#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1426(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Create a new Janet environment
    JanetTable *env = janet_core_env(NULL);

    // Check if data is not null and size is greater than zero
    if (data && size > 0) {
        // Convert the input data to a Janet string
        Janet str = janet_stringv(data, size);

        // Create a tuple to call a Janet function
        Janet args[1] = {str};

        // Resolve the 'dostring' function
        Janet resolved;
        if (janet_resolve(env, janet_csymbol("dostring"), &resolved) && janet_checktype(resolved, JANET_FUNCTION)) {
            // Call a Janet function (e.g., 'dostring') with the input
            JanetFunction *func = janet_unwrap_function(resolved);
            JanetFiber *fiber = janet_fiber(func, 64, 1, args);
            if (fiber) {
                Janet result;
                janet_schedule(fiber, result);
                janet_continue(fiber, result, &result);
            }
        }
    }

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}