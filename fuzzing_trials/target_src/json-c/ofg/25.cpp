#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// Assuming the definition of the struct array_list is available
struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

extern "C" void *array_list_get_idx(struct array_list *, size_t);

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create an array_list object
    struct array_list list;

    // Set the capacity and size
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 1000);
    list.size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.capacity);

    // Allocate memory for the array
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));

    if (list.array == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1); // Allocate 1 byte for each element
        if (list.array[i] == nullptr) {
            // If allocation fails, free already allocated memory and exit
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Get an index to access
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.size - 1);

    // Call the function-under-test
    void *result = array_list_get_idx(&list, index);

    // Free allocated memory
    for (size_t i = 0; i < list.size; ++i) {
        free(list.array[i]);
    }
    free(list.array);

    return 0;
}