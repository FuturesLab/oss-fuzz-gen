#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Define the array_list structure
struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

// Function to free the memory allocated for an array_list
void array_list_free(struct array_list *list) {
    if (!list || !list->array) return;
    for (size_t i = 0; i < list->size; ++i) {
        free(list->array[i]);
    }
    free(list->array);
    list->array = NULL;
    list->size = 0;
    list->capacity = 0;
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a new array_list
    struct array_list list;

    // Initialize the size and capacity
    list.size = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 100);
    list.capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(list.size, 200);

    // Allocate memory for the array
    list.array = static_cast<void **>(malloc(list.capacity * sizeof(void *)));
    if (!list.array) {
        return 0; // If allocation fails, exit early
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1); // Allocate 1 byte for each element
        if (!list.array[i]) {
            // If allocation fails, free previously allocated memory and exit
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Call the function-under-test
    array_list_free(&list);

    return 0;
}