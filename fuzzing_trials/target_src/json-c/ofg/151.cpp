#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

extern "C" {

struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

int array_list_shrink(struct array_list *, size_t);

} // extern "C"

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create an array_list instance
    struct array_list list;

    // Determine the capacity of the list
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 1000);

    // Allocate memory for the array
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));
    if (list.array == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.capacity; ++i) {
        list.array[i] = malloc(1); // Allocate 1 byte to ensure non-null pointers
    }

    // Set the size of the list
    list.size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.capacity);

    // Determine the new size to shrink the list to
    size_t new_size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.size);

    // Call the function-under-test
    array_list_shrink(&list, new_size);

    // Free allocated memory
    for (size_t i = 0; i < list.capacity; ++i) {
        free(list.array[i]);
    }
    free(list.array);

    return 0;
}