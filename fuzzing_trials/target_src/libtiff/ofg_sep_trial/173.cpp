#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Define and initialize tmsize_t variables
    tmsize_t nmemb = 1; // Number of elements
    tmsize_t size_per_elem = 1; // Size of each element

    // Ensure size is at least 2 to extract two tmsize_t values from data
    if (size >= 2 * sizeof(tmsize_t)) {
        // Extract tmsize_t values from the input data
        nmemb = *reinterpret_cast<const tmsize_t*>(data);
        size_per_elem = *reinterpret_cast<const tmsize_t*>(data + sizeof(tmsize_t));
    }

    // Call the function-under-test
    void *result = _TIFFcalloc(nmemb, size_per_elem);

    // Free the allocated memory if not NULL
    if (result != NULL) {
        _TIFFfree(result);
    }

    return 0;
}