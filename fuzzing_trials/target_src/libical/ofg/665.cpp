#include <stdint.h>
#include <stddef.h>

// Wrap the C library functions in extern "C"
extern "C" {
    #include <libical/icalproperty.h> // Assuming the correct path to the header file
    #include <libical/icalderivedproperty.h> // Include the header where the function is declared

    // Function signature from the project
    // Note: Removed the incorrect function signature since it conflicts with the actual declaration
}

extern "C" int LLVMFuzzerTestOneInput_665(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = new char[size + 1];
    for (size_t i = 0; i < size; i++) {
        str[i] = data[i] % 128; // Ensure valid ASCII characters
    }
    str[size] = '\0';

    // Call the function-under-test with a sentinel value (nullptr) for variadic arguments
    icalproperty *result = icalproperty_vanew_recurexpand(str, nullptr);

    // Clean up
    delete[] str;
    if (result != nullptr) {
        icalproperty_free(result);
    }

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

    LLVMFuzzerTestOneInput_665(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
