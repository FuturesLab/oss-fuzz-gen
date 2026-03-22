#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    void plist_mem_free(void *);
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Allocate memory and ensure it is not NULL
    void *memory = malloc(size > 0 ? size : 1);  // Ensure at least 1 byte is allocated

    // Call the function-under-test
    plist_mem_free(memory);

    return 0;
}