#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iostream>

extern "C" {
    // Assuming the function is declared in a header file
    bool icalvalue_decode_ical_string(const char *input, char *output, int output_size);
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for the function call
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input and output strings
    const char *input = reinterpret_cast<const char *>(data);

    // Define a reasonable size for the output buffer
    int output_size = 256;
    char output[output_size];

    // Copy input data to ensure null-termination
    char *input_copy = new char[size + 1];
    std::memcpy(input_copy, input, size);
    input_copy[size] = '\0'; // Null-terminate the input string

    // Initialize the output buffer to ensure it's in a known state
    std::memset(output, 0, output_size);

    // Check if the input is valid before calling the function
    if (std::strlen(input_copy) == 0) {
        delete[] input_copy;
        return 0;
    }

    // Call the function-under-test
    bool result = icalvalue_decode_ical_string(input_copy, output, output_size);

    // Optionally, print the result for debugging purposes
    std::cout << "Result: " << result << ", Output: " << output << std::endl;

    // Clean up allocated memory
    delete[] input_copy;

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

    LLVMFuzzerTestOneInput_52(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
