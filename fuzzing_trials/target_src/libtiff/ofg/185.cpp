#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the parameters
    if (size < 3) {
        return 0;
    }

    // Initialize the parameters for TIFFWarningExt
    thandle_t fd = const_cast<uint8_t*>(data); // Remove const qualifier by using const_cast
    const char *module = reinterpret_cast<const char *>(data + 1); // Use the second byte onwards as a module name
    const char *fmt = reinterpret_cast<const char *>(data + 2); // Use the third byte onwards as a format string

    // Call TIFFWarningExt with the initialized parameters
    TIFFWarningExt(fd, module, "%s", fmt); // Treat the format string as an argument

    return 0;
}