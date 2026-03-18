#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two tmsize_t values
    if (size < sizeof(tmsize_t) * 2) {
        return 0;
    }

    // Extract two tmsize_t values from the input data
    tmsize_t count = *(reinterpret_cast<const tmsize_t*>(data));
    tmsize_t size_per_element = *(reinterpret_cast<const tmsize_t*>(data + sizeof(tmsize_t)));

    // Call the function-under-test
    void* result = _TIFFcalloc(count, size_per_element);

    // Free the allocated memory if allocation was successful
    if (result != nullptr) {
        _TIFFfree(result);
    }

    return 0;
}