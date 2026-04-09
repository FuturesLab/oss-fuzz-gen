#include <stddef.h>
#include <stdint.h>

// Assuming the janet_loop function is defined elsewhere and linked during compilation
void janet_loop();

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Call the function-under-test
    janet_loop();
    return 0;
}