#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <curl/curl.h>
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Allocate memory and copy the input data into it
    void *memory = malloc(size);
    if (memory == nullptr) {
        return 0;
    }
    memcpy(memory, data, size);

    // Call the function-under-test
    curl_free(memory);

    return 0;
}