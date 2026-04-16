#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

extern void janet_async_in_flight(JanetFiber *);

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    JanetFiber *fiber = NULL;

    // Ensure the size is sufficient to create a JanetFiber structure
    if (size >= sizeof(JanetFiber)) {
        // Allocate memory for the JanetFiber structure
        fiber = (JanetFiber *)malloc(sizeof(JanetFiber));
        if (fiber == NULL) {
            return 0; // If memory allocation fails, return early
        }

        // Initialize the JanetFiber structure with the input data
        // Assuming the data can be directly copied into the JanetFiber structure
        memcpy(fiber, data, sizeof(JanetFiber));

        // Call the function-under-test
        janet_async_in_flight(fiber);

        // Free the allocated memory
        free(fiber);
    }

    return 0;
}