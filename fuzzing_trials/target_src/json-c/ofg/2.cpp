#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/json-c/arraylist.h" // Include the header for array_list_length

// Function-under-test
size_t array_list_length(struct array_list *);

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create an instance of struct array_list
    struct array_list list;

    // Initialize the array_list fields
    list.length = fuzzed_data.ConsumeIntegral<size_t>();
    list.size = fuzzed_data.ConsumeIntegral<size_t>();

    // Allocate memory for the array, ensuring it's not NULL
    list.array = static_cast<void **>(malloc(list.size * sizeof(void *)));
    if (list.array == nullptr) {
        return 0; // Exit if memory allocation failed
    }

    // Fill the array with non-null pointers
    for (size_t i = 0; i < list.size; ++i) {
        list.array[i] = malloc(1); // Allocate a byte for each element
        if (list.array[i] == nullptr) {
            // If allocation fails, clean up and exit
            for (size_t j = 0; j < i; ++j) {
                free(list.array[j]);
            }
            free(list.array);
            return 0;
        }
    }

    // Call the function-under-test
    size_t result = array_list_length(&list);

    // Clean up allocated memory
    for (size_t i = 0; i < list.size; ++i) {
        free(list.array[i]);
    }
    free(list.array);

    return 0;
}