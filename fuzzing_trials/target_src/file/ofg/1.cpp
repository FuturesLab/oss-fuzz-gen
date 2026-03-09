#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the header file where magic_version is declared
    #include "magic.h"
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version = magic_version();

    // Use the version variable in some way to avoid unused variable warning
    // Here we simply return it as part of the function's return value
    return version;
}