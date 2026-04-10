#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_368(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to create a pointer
    if (size < sizeof(void *)) {
        return 0;
    }

    // Cast the data to a pointer
    void *ptr = (void *)data;

    // Ensure that the pointer is not null
    if (ptr == NULL) {
        return 0;
    }

    // Call the function-under-test using the macro
    Janet result = janet_wrap_pointer(ptr);

    // Optionally, perform operations with 'result' if needed

    return 0;
}