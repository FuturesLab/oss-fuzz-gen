#include "ucl.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h> // Include for uint8_t
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int fd = *(const int *)data;

    // Call the function-under-test
    struct ucl_emitter_functions *funcs = ucl_object_emit_fd_funcs(fd);

    // Clean up if necessary
    if (funcs != NULL) {
        free(funcs);
    }

    return 0;
}