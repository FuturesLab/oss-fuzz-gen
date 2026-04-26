#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// Assuming the function is defined in an external C library
extern "C" {
    bool icalvalue_encode_ical_string(const char *input, char *output, int output_size);
}

extern "C" int LLVMFuzzerTestOneInput_1316(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for input and output strings
    char *input = new char[size + 1];
    char *output = new char[size + 1];

    // Copy data to input and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Initialize the output buffer with a known size
    int output_size = static_cast<int>(size + 1);

    // Call the function-under-test
    bool result = icalvalue_encode_ical_string(input, output, output_size);

    // Clean up allocated memory
    delete[] input;
    delete[] output;

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

    LLVMFuzzerTestOneInput_1316(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
