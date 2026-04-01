#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

// Dummy function to simulate TIFFError behavior
void TIFFError(const char *module, const char *fmt, void *ap) {
    // For the purpose of this example, we'll just print the module and format
    printf("Module: %s, Format: %s\n", module, fmt);
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure there's enough data for module and format strings
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts for module and format strings
    size_t module_len = data[0] % (size - 1) + 1; // Ensure at least 1 character
    size_t fmt_len = size - module_len;

    // Allocate memory for module and format strings
    char *module = new char[module_len + 1];
    char *fmt = new char[fmt_len + 1];

    // Copy data into the strings and null-terminate them
    memcpy(module, data + 1, module_len);
    module[module_len] = '\0';

    memcpy(fmt, data + 1 + module_len, fmt_len);
    fmt[fmt_len] = '\0';

    // Call the function-under-test
    TIFFError(module, fmt, nullptr);

    // Clean up
    delete[] module;
    delete[] fmt;

    return 0;
}