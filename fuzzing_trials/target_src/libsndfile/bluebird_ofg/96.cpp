#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream> // For logging

// Assuming these structures are defined in the relevant headers
typedef struct {
    // Example fields, actual fields may vary
    const void *chunk_data;
    size_t chunk_size;
} SF_CHUNK_ITERATOR;

typedef struct {
    // Example fields, actual fields may vary
    void *data;
    size_t size;
} SF_CHUNK_INFO;

// Function-under-test
extern "C" int sf_get_chunk_data(const SF_CHUNK_ITERATOR *, SF_CHUNK_INFO *);

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to avoid buffer overflow
    if (size < sizeof(SF_CHUNK_ITERATOR)) {
        return 0;
    }

    // Initialize SF_CHUNK_ITERATOR and SF_CHUNK_INFO
    SF_CHUNK_ITERATOR iterator;
    SF_CHUNK_INFO info;

    // Ensure chunk_data is not NULL
    iterator.chunk_data = (const void *)data;
    iterator.chunk_size = size;

    // Initialize SF_CHUNK_INFO fields
    info.data = malloc(size);  // Allocate memory for data
    if (info.data == NULL) {
        return 0;  // Handle allocation failure
    }
    info.size = size;

    // Copy input data to info.data to avoid accessing uninitialized memory
    memcpy(info.data, data, size);

    // Call the function-under-test
    int result = sf_get_chunk_data(&iterator, &info);

    // Check if sf_get_chunk_data modified info.size to ensure it does not exceed allocated size
    if (info.size > size) {
        // Log an error or handle the situation as needed
        std::cerr << "Error: info.size exceeds allocated size" << std::endl;
    }

    // Clean up
    free(info.data);

    return result;
}