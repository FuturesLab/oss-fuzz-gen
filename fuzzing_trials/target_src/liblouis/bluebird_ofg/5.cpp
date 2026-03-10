#include <cstddef>  // For size_t
#include <cstdint>  // For uint8_t

extern "C" {
    #include "../../liblouis/liblouis.h"
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Since lou_free() does not take any parameters, we can directly call it
    lou_free();

    return 0;
}