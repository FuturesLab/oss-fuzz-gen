#include <cstdint>
#include <cstddef>
#include <cstring>

// Assuming the function is defined in a C library
extern "C" {
    int lou_checkTable(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated
    char *null_terminated_data = new char[size + 1];
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    int result = lou_checkTable(null_terminated_data);

    // Clean up
    delete[] null_terminated_data;

    return 0;
}