#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdio>

extern "C" {
    // Forward declaration of the function-under-test
    void TIFFWarning(const char *module, const char *fmt, void *dummy);
}

extern "C" int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to split into meaningful strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the module and fmt strings
    size_t mid = size / 2;
    char module[mid + 1];
    char fmt[size - mid + 1];

    // Copy the data into the module and fmt strings, ensuring null termination
    std::memcpy(module, data, mid);
    module[mid] = '\0';

    std::memcpy(fmt, data + mid, size - mid);
    fmt[size - mid] = '\0';

    // Dummy pointer, can be used for additional context if needed
    void *dummy = reinterpret_cast<void *>(0x1);

    // Call the function-under-test
    TIFFWarning(module, fmt, dummy);

    return 0;
}