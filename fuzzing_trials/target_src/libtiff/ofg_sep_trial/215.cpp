#include <cstdint>
#include <cstdio>
#include <cstring>

// Function-under-test declaration
extern "C" {
    void TIFFWarning(const char *module, const char *fmt, void *ap);
}

extern "C" int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract strings
    if (size < 2) {
        return 0;
    }

    // Split the data into two strings
    size_t mid = size / 2;
    char module[256];
    char fmt[256];

    // Copy data into module and fmt strings ensuring null-termination
    size_t module_len = (mid < 255) ? mid : 255;
    size_t fmt_len = (size - mid < 255) ? size - mid : 255;

    std::memcpy(module, data, module_len);
    std::memcpy(fmt, data + mid, fmt_len);

    module[module_len] = '\0';
    fmt[fmt_len] = '\0';

    // Call the function-under-test
    TIFFWarning(module, fmt, nullptr);

    return 0;
}