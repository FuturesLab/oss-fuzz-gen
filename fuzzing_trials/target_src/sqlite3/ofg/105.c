#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Dummy function to simulate DW_TAG_subroutine_typeInfinite loop
// In practice, this should be replaced with an actual function pointer
int dummy_function_105() {
    return 0;
}

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure the function pointer is not NULL
    int (*func_ptr)() = dummy_function_105;

    // Call the function-under-test
    int result = sqlite3_cancel_auto_extension((void (*)())func_ptr);

    // Use the result to avoid compiler optimizations (if needed)
    (void)result;

    return 0;
}