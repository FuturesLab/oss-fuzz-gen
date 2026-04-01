#include <cstdint>
#include <cstdio>
#include <tiffio.h>

extern "C" {

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create meaningful strings
    if (size < 3) return 0;

    // Initialize parameters for TIFFWarningExt
    thandle_t handle = (thandle_t)0x1234; // Arbitrary non-null handle
    const char *module = reinterpret_cast<const char*>(data);
    const char *fmt = reinterpret_cast<const char*>(data + 1);
    void *clientData = reinterpret_cast<void*>(0x5678); // Arbitrary non-null pointer

    // Call the function under test
    TIFFWarningExt(handle, module, fmt, clientData);

    return 0;
}

}