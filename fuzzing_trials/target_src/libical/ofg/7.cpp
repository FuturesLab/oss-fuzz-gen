#include <stdint.h>
#include <stddef.h>

// Wrap the inclusion of C headers and functions in extern "C"
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input = new char[size + 1];
    if (input == nullptr) {
        return 0;
    }

    // Copy the data into the input buffer and null-terminate it
    for (size_t i = 0; i < size; ++i) {
        input[i] = static_cast<char>(data[i]);
    }
    input[size] = '\0';

    // Call the function-under-test
    icalcomponent_kind kind = icalcomponent_string_to_kind(input);

    // Clean up
    delete[] input;

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_7(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
