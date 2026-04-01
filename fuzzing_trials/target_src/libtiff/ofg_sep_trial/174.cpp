#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" {
    void* _TIFFcalloc(tmsize_t nmemb, tmsize_t size);
}

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract two tmsize_t values
    if (size < 2 * sizeof(tmsize_t)) {
        return 0;
    }

    // Extract two tmsize_t values from the input data
    tmsize_t nmemb = *reinterpret_cast<const tmsize_t*>(data);
    tmsize_t elem_size = *reinterpret_cast<const tmsize_t*>(data + sizeof(tmsize_t));

    // Call the function under test
    void* result = _TIFFcalloc(nmemb, elem_size);

    // Free the allocated memory if allocation was successful
    if (result != NULL) {
        _TIFFfree(result);
    }

    return 0;
}