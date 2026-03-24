#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    struct array_list {
        void **array;
        size_t size;
        size_t capacity;
    };

    int array_list_put_idx(struct array_list *, size_t, void *);
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create and initialize an array_list
    struct array_list list;
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 100); // Ensure capacity is at least 1
    list.size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.capacity); // size should be within capacity
    list.array = (void **)malloc(list.capacity * sizeof(void *));
    if (list.array == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1); // Allocate dummy memory for each element
        if (list.array[i] == NULL) {
            // If allocation fails, free already allocated memory and exit
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Consume a size_t index
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.capacity - 1);

    // Consume a void* value
    void *value = malloc(1); // Allocate dummy memory for the value
    if (value == NULL) {
        // Free previously allocated memory and exit if allocation fails
        for (size_t i = 0; i < list.size; ++i) {
            free(list.array[i]);
        }
        free(list.array);
        return 0;
    }

    // Call the function-under-test
    int result = array_list_put_idx(&list, index, value);

    // If the function replaces an existing element, free it to avoid double-free
    if (result == 0 && index < list.size && list.array[index] != value) {
        free(list.array[index]);
    }

    // Free allocated memory
    for (size_t i = 0; i < list.size; ++i) {
        if (list.array[i] != value) { // Ensure we don't double-free 'value'
            free(list.array[i]);
        }
    }
    free(list.array);
    free(value);

    return 0;
}