#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

extern "C" int array_list_insert_idx(struct array_list *, size_t, void *);

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t) * 2 + sizeof(void *)) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data(data, size);

    // Initialize array_list
    struct array_list list;
    list.size = fuzzed_data.ConsumeIntegral<size_t>();
    list.capacity = fuzzed_data.ConsumeIntegral<size_t>();
    
    // Ensure capacity is at least as large as size
    if (list.capacity < list.size) {
        list.capacity = list.size;
    }

    // Allocate memory for the array
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));
    if (list.array == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1); // Allocate dummy memory
        if (list.array[i] == nullptr) {
            // If allocation fails, free already allocated memory and exit
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Get the index for insertion
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.size);

    // Allocate memory for the new element
    void *new_element = malloc(1);
    if (new_element == nullptr) {
        // Free allocated memory and exit if allocation fails
        for (size_t i = 0; i < list.size; ++i) {
            free(list.array[i]);
        }
        free(list.array);
        return 0;
    }

    // Call the function-under-test
    array_list_insert_idx(&list, index, new_element);

    // Free allocated memory
    for (size_t i = 0; i < list.size; ++i) {
        free(list.array[i]);
    }
    free(list.array);

    return 0;
}