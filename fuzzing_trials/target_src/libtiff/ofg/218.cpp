#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstring>

// Assuming the TIFFWarning function is defined in a C library
extern "C" {
    void TIFFWarning(const char *, const char *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for two strings and a dummy void pointer
    if (size < 3) return 0;

    // Split the data into two strings and a dummy pointer
    size_t str1_len = size / 3;
    size_t str2_len = size / 3;
    size_t void_ptr_offset = 2 * (size / 3);

    // Create null-terminated strings
    char *str1 = new char[str1_len + 1];
    char *str2 = new char[str2_len + 1];
    std::memcpy(str1, data, str1_len);
    std::memcpy(str2, data + str1_len, str2_len);
    str1[str1_len] = '\0';
    str2[str2_len] = '\0';

    // Dummy void pointer as a string
    const char *dummy_ptr = reinterpret_cast<const char *>(data + void_ptr_offset);

    // Call the function-under-test
    TIFFWarning(str1, str2, dummy_ptr);

    // Clean up
    delete[] str1;
    delete[] str2;

    return 0;
}