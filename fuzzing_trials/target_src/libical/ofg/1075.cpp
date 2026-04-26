#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

// Assuming the function is declared in an external C library
extern "C" {
    void icaltimezone_set_tzid_prefix(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_1075(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Ensure the input data is null-terminated to be used as a C string
    char *tzid_prefix = new char[size + 1];
    if (tzid_prefix == nullptr) {
        return 0; // Memory allocation failed
    }

    // Copy the input data and null-terminate it
    memcpy(tzid_prefix, data, size);
    tzid_prefix[size] = '\0';

    // Check if the input is not just null characters to ensure meaningful input
    bool has_non_null_char = false;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != '\0') {
            has_non_null_char = true;
            break;
        }
    }

    if (has_non_null_char) {
        // Call the function-under-test
        icaltimezone_set_tzid_prefix(tzid_prefix);
    }

    // Clean up
    delete[] tzid_prefix;

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1075(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
