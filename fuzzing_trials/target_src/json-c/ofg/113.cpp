#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    struct array_list;
    typedef void (array_list_free_fn)(void *);
    struct array_list * array_list_new(array_list_free_fn *);
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Define a dummy free function
    auto dummy_free_fn = [](void *ptr) { /* no-op */ };

    // Call the function-under-test with the dummy free function
    struct array_list *list = array_list_new(dummy_free_fn);

    // Normally, you would perform operations on the list here and then free it
    // but since this is a fuzzing harness, we focus on calling the function.

    return 0;
}