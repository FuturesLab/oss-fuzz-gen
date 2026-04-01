#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Assuming the definition of struct array_list and related functions are provided elsewhere
struct array_list {
    void **array;
    size_t length;
    size_t capacity;
};

extern "C" size_t array_list_length(struct array_list *);

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a dummy array_list structure
    struct array_list list;
    list.length = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 1000);
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(list.length, 2000);

    // Allocate memory for the array
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));
    if (list.array == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Populate the array with non-null pointers
    for (size_t i = 0; i < list.length; ++i) {
        list.array[i] = &list; // Point to the list itself to ensure non-null pointers
    }

    // Call the function-under-test
    size_t result = array_list_length(&list);

    // Free the allocated memory
    free(list.array);

    return 0;
}