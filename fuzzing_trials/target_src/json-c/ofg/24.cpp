#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct array_list {
    void **array;
    size_t size;
    size_t capacity;
};

extern "C" void * array_list_get_idx(struct array_list *, size_t);

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    size_t list_capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(1, 100);
    size_t list_size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list_capacity);

    struct array_list list;
    list.capacity = list_capacity;
    list.size = list_size;
    list.array = (void **)malloc(list_capacity * sizeof(void *));

    if (list.array == nullptr) {
        return 0;
    }

    for (size_t i = 0; i < list_size; ++i) {
        list.array[i] = (void *)fuzzed_data.ConsumeIntegral<uintptr_t>();
    }

    size_t index = fuzzed_data.ConsumeIntegralInRange<size_t>(0, list_size - 1);

    void *result = array_list_get_idx(&list, index);

    free(list.array);

    return 0;
}