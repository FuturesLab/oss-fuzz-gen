#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    // Function prototype for the function-under-test
    void* _TIFFcalloc(tmsize_t nmemb, tmsize_t size);
}

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two tmsize_t values
    if (size < 2 * sizeof(tmsize_t)) {
        return 0;
    }

    // Extract two tmsize_t values from the input data
    tmsize_t nmemb = *(reinterpret_cast<const tmsize_t*>(data));
    tmsize_t element_size = *(reinterpret_cast<const tmsize_t*>(data + sizeof(tmsize_t)));

    // Ensure the values are non-zero to avoid trivial cases
    if (nmemb == 0 || element_size == 0) {
        nmemb = 1;
        element_size = 1;
    }

    // Call the function-under-test
    void* result = _TIFFcalloc(nmemb, element_size);

    // Free the allocated memory if the allocation was successful
    if (result != nullptr) {
        _TIFFfree(result);
    }

    return 0;
}