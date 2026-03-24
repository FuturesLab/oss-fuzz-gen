#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>

// Define the array_list structure before using it in the function
struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

// Mock definition of array_list_put_idx for demonstration purposes
int array_list_put_idx(struct array_list* list, size_t index, void* value) {
    if (index >= list->size) {
        return -1; // Error: index out of bounds
    }
    free(list->array[index]); // Free the existing element
    list->array[index] = value; // Insert the new value
    return 0; // Success
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t) * 2) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data(data, size);

    // Initialize array_list
    struct array_list list;
    list.size = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 100);
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(list.size, 200);
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));
    if (list.array == nullptr) {
        return 0;
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1);  // Allocate 1 byte for each element
        if (list.array[i] == nullptr) {
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Consume index and value
    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list.size - 1);
    std::string value_data = fuzzed_data.ConsumeRandomLengthString(1);
    if (value_data.size() != 1) {
        // Ensure the value_data is exactly 1 byte
        for (size_t i = 0; i < list.size; ++i) {
            free(list.array[i]);
        }
        free(list.array);
        return 0;
    }
    void *value = malloc(value_data.size());
    if (value != nullptr) {
        memcpy(value, value_data.data(), value_data.size());
    }

    // Call the function-under-test
    int result = array_list_put_idx(&list, index, value);

    // Clean up
    for (size_t i = 0; i < list.size; ++i) {
        if (i != index || result != 0) {
            free(list.array[i]);
        }
    }
    free(list.array);
    if (result != 0) {
        free(value);
    }

    return 0;
}