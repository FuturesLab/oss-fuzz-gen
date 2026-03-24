#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>

// Assuming array_list_free_fn is a typedef for a function pointer
typedef void(array_list_free_fn)(void *);

// Mock implementation of the function-under-test
struct array_list {
  int *elements;
  int size;
};

struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size) {
  if (initial_size <= 0) {
    return nullptr;
  }

  struct array_list *list = (struct array_list *)malloc(sizeof(struct array_list));
  if (!list) {
    return nullptr;
  }

  list->elements = (int *)malloc(initial_size * sizeof(int));
  if (!list->elements) {
    free(list);
    return nullptr;
  }

  list->size = initial_size;
  return list;
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Randomize the behavior of the free function
  array_list_free_fn *free_fn = [](void *ptr) {
    if (ptr && rand() % 2 == 0) { // Randomly decide whether to free the memory
      free(ptr);
    }
  };

  // Allow initial_size to be zero or negative to test edge cases
  int initial_size = fuzzed_data.ConsumeIntegral<int>();

  // Call the function-under-test
  struct array_list *list = array_list_new2(free_fn, initial_size);

  // Clean up if necessary
  if (list) {
    free_fn(list->elements);
    free(list);
  }

  return 0;
}